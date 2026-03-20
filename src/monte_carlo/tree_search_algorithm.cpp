#include <monte_carlo/tree_search_algorithm.h>
#include <monte_carlo/models/node.h>
#include <logging/colors.h>
#include <cmath>
#include <monte_carlo/common_aliases.h>
#include <monte_carlo/models/action.h>

#include "monte_carlo/models/simulation_result.h"

using sophia::monte_carlo::MonteCarloTreeSearch;
using sophia::monte_carlo::models::Node;
using std::shared_ptr;

sophia::monte_carlo::action_ptr MonteCarloTreeSearch::run(
    const std::shared_ptr<Node> &root,
    int iterations,
    const logger_ptr& logger)
{
    if (!root)
    {
        if (logger) logger->error("MCTS::run called with a null root node.");
        throw std::invalid_argument("Root node cannot be null.");
    }
    
    if (iterations < 0 || iterations > 20000)
    {
        if (logger) logger->error("Invalid number of iterations: {}", iterations);
        throw std::invalid_argument("Invalid number of iterations");
    }

    for(int i = 0; i < iterations; i++)
    {
        if (logger) logger->info("\n--- Iteration {} ---", i + 1);

        // From the root node, we are deciding which action to take.
        // If there are no child actions, we can't do anything.
        if (root->IsLeafNode()) root->Expand();

        // If expansion failed.  return because there is no choice to make.
        if (root->IsLeafNode()) return nullptr;

        shared_ptr<Node> current = root;

        bool expanded = false;
        double iteration_reward = 0.0;

        // --- 1. Selection ---
        if (logger) logger->info("{}", logging::colors::phase_selection("Phase 1: Selection"));
        while (!current->IsLeafNode())
        {
            const auto action = current->SelectBestAction();
            if (!action || !action->Target())
            {
                if (logger) logger->error("Selection phase returned a null action or target node from non-leaf node '{}'.", current->Name());
                // Break the loop to prevent crash, will proceed to rollout from current node
                break;
            }
            current = action->Target();
        }
        if (logger) logger->debug("Selection finished at node: {}", logging::colors::highlight_node(current->Name()));

        // --- 2. Expansion ---
        if (logger) logger->info("{}", logging::colors::phase_expansion("Phase 2: Expansion"));
        if (current->HasBeenSampled() && !current->IsTerminalState())
        {
            if (logger) logger->debug("Node '{}' has been sampled. Expanding...", current->Name());
            auto first_expansion_node = current->Expand();
            if (first_expansion_node)
            {
                current = first_expansion_node;
                expanded = true;
            }
            else
            {
                 if (logger) logger->debug("Node '{}' did not expand (might be terminal or have no actions).", current->Name());
            }
        }
        else
        {
            if (logger)
            {
                if (current->IsTerminalState())
                    logger->debug("Node '{}' is a terminal state. Skipping expansion.", current->Name());
                else
                    logger->debug("Node '{}' has not been sampled. Skipping expansion.", current->Name());
            }
        }

        // --- 3. Rollout (Simulation) ---
        if (logger) logger->info("{}", logging::colors::phase_rollout("Phase 3: Rollout (Simulation)"));
        const_simulation_result_ptr reward = current->Rollout();
        iteration_reward = reward ? reward->Reward() : 0.0;
        if (logger) 
        {
            auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("Rollout from {} → reward: {}", 
                logging::colors::highlight_node(current->Name()), reward_str);
        }

        // --- 4. Backpropagation ---
        if (logger) logger->info("{}", logging::colors::phase_backprop("Phase 4: Backpropagation"));
        current->Backpropagate(reward);
        
        // Iteration summary
        if (logger) 
        {
            const auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("Iteration {} summary: expanded={}, rollout_reward={}, final_node={}", 
                i + 1, expanded ? "yes" : "no", reward_str, logging::colors::highlight_node(current->Name()));
        }
    }

    const auto best_action = root->SelectAction();
    
    if (logger)
    {
        logger->info("\n--- MCTS Complete: Final Action Summary ---");
        logger->info("{:<25} | {:<12} | {:<15} | {:<12} | {:<12} | {:<10}", 
            "Action (-> Node)", "Visits", "Total Reward", "Avg Reward", "UCB (c=2)", "Selected");
        logger->info("--------------------------------------------------------------------------------------------------------");

        auto final_actions = root->GetAvailableActions();
        
        for (const auto& action : final_actions)
        {
            auto target = action->Target();
            if (target && target->VisitCount() > 0)
            {
                double avg_reward = target->TotalReward() / target->VisitCount();
                double ucb_value = target->UpperConfidenceBound(2);
                std::string action_name = "'" + action->Name() + "' -> '" + target->Name() + "'";
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                
                const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->VisitCount()));
                const auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", target->TotalReward()));
                const auto avg_str = logging::colors::highlight_reward(std::format("{:.4f}", avg_reward));
                
                if (std::isinf(ucb_value))
                {
                    const auto ucb_str = logging::colors::highlight_ucb("inf");
                    logger->info("{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}", 
                        action_name, visits_str, reward_str, avg_str, ucb_str, selected_str);
                }
                else
                {
                    const auto ucb_str = logging::colors::highlight_ucb(std::format("{:.4f}", ucb_value));
                    logger->info("{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}", 
                        action_name, visits_str, reward_str, avg_str, ucb_str, selected_str);
                }
            }
            else
            {
                std::string action_name = action->Name();
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                logger->info("{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}", 
                    action_name, "0", "N/A", "N/A", "N/A", selected_str);
            }
        }
        logger->info("--------------------------------------------------------------------------------------------------------");
    }
    if (logger && best_action && best_action->Target())
    {
        auto target = best_action->Target();
        double avg_reward = target->VisitCount() > 0 ? target->TotalReward() / target->VisitCount() : 0.0;
        const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->VisitCount()));
        const auto total_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", target->TotalReward()));
        const auto avg_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", avg_reward));
        logger->info("=> Best Action Selected: '{}' -> {} (visits={}, total_reward={}, avg_reward={})", 
            best_action->Name(), logging::colors::highlight_node(target->Name()),
            visits_str, total_reward_str, avg_reward_str);
    } else if (logger)
    {
        logger->warn("=> No best action could be selected.");
    }

    return best_action;
}

