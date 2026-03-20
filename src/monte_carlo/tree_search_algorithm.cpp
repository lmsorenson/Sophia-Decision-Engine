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
        if (root->is_leaf_node()) root->expand();

        // If expansion failed.  return because there is no choice to make.
        if (root->is_leaf_node()) return nullptr;

        shared_ptr<Node> current = root;

        bool expanded = false;
        double iteration_reward = 0.0;

        // --- 1. Selection ---
        if (logger) logger->info("{}", logging::colors::phase_selection("Phase 1: Selection"));
        while (!current->is_leaf_node())
        {
            const auto action = current->select_best_action();
            if (!action || !action->target())
            {
                if (logger) logger->error("Selection phase returned a null action or target node from non-leaf node '{}'.", current->name());
                // Break the loop to prevent crash, will proceed to rollout from current node
                break;
            }
            current = action->target();
        }
        if (logger) logger->debug("Selection finished at node: {}", logging::colors::highlight_node(current->name()));

        // --- 2. Expansion ---
        if (logger) logger->info("{}", logging::colors::phase_expansion("Phase 2: Expansion"));
        if (current->has_been_sampled() && !current->is_terminal_state())
        {
            if (logger) logger->debug("Node '{}' has been sampled. Expanding...", current->name());
            auto first_expansion_node = current->expand();
            if (first_expansion_node)
            {
                current = first_expansion_node;
                expanded = true;
            }
            else
            {
                 if (logger) logger->debug("Node '{}' did not expand (might be terminal or have no actions).", current->name());
            }
        }
        else
        {
            if (logger)
            {
                if (current->is_terminal_state())
                    logger->debug("Node '{}' is a terminal state. Skipping expansion.", current->name());
                else
                    logger->debug("Node '{}' has not been sampled. Skipping expansion.", current->name());
            }
        }

        // --- 3. Rollout (Simulation) ---
        if (logger) logger->info("{}", logging::colors::phase_rollout("Phase 3: rollout (Simulation)"));
        const_simulation_result_ptr reward = current->rollout();
        iteration_reward = reward ? reward->reward() : 0.0;
        if (logger) 
        {
            auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("rollout from {} → reward: {}", 
                logging::colors::highlight_node(current->name()), reward_str);
        }

        // --- 4. Backpropagation ---
        if (logger) logger->info("{}", logging::colors::phase_backprop("Phase 4: Backpropagation"));
        current->backpropagate(reward);
        
        // Iteration summary
        if (logger) 
        {
            const auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("Iteration {} summary: expanded={}, rollout_reward={}, final_node={}", 
                i + 1, expanded ? "yes" : "no", reward_str, logging::colors::highlight_node(current->name()));
        }
    }

    const auto best_action = root->select_action();
    
    if (logger)
    {
        logger->info("\n--- MCTS Complete: Final Action Summary ---");
        logger->info("{:<25} | {:<12} | {:<15} | {:<12} | {:<12} | {:<10}", 
            "Action (-> Node)", "Visits", "Total reward", "Avg reward", "UCB (c=2)", "Selected");
        logger->info("--------------------------------------------------------------------------------------------------------");

        auto final_actions = root->get_available_actions();
        
        for (const auto& action : final_actions)
        {
            auto target = action->target();
            if (target && target->visit_count() > 0)
            {
                double avg_reward = target->total_reward() / target->visit_count();
                double ucb_value = target->upper_confidence_bound(2);
                std::string action_name = "'" + action->name() + "' -> '" + target->name() + "'";
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                
                const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->visit_count()));
                const auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", target->total_reward()));
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
                std::string action_name = action->name();
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                logger->info("{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}", 
                    action_name, "0", "N/A", "N/A", "N/A", selected_str);
            }
        }
        logger->info("--------------------------------------------------------------------------------------------------------");
    }
    if (logger && best_action && best_action->target())
    {
        auto target = best_action->target();
        double avg_reward = target->visit_count() > 0 ? target->total_reward() / target->visit_count() : 0.0;
        const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->visit_count()));
        const auto total_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", target->total_reward()));
        const auto avg_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", avg_reward));
        logger->info("=> Best Action Selected: '{}' -> {} (visits={}, total_reward={}, avg_reward={})", 
            best_action->name(), logging::colors::highlight_node(target->name()),
            visits_str, total_reward_str, avg_reward_str);
    } else if (logger)
    {
        logger->warn("=> No best action could be selected.");
    }

    return best_action;
}

