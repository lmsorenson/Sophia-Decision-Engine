#include <monte_carlo/tree_search_algorithm.h>
#include <monte_carlo/models/node.h>
#include <monte_carlo/output/print_dashboard.h>
#include <logging/colors.h>
#include <monte_carlo/common_aliases.h>
#include <monte_carlo/models/action.h>
#include <logging/ilogger.h>

#include "monte_carlo/models/simulation_result.h"

using sophia::monte_carlo::MonteCarloTreeSearch;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::output::Dashboard;
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
        if (logger) logger->info(logging::LogChannel::Trace, "\n--- Iteration {} ---", i + 1);

        // From the root node, we are deciding which action to take.
        // If there are no child actions, we can't do anything.
        if (root->is_leaf_node()) root->expand();

        // If expansion failed.  return because there is no choice to make.
        if (root->is_leaf_node()) return nullptr;

        shared_ptr<Node> current = root;

        bool expanded = false;
        double iteration_reward = 0.0;

        // --- 1. Selection ---
        if (logger) logger->info(logging::LogChannel::Trace, "{}", logging::colors::phase_selection("Phase 1: Selection"));
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
        if (logger) logger->info(logging::LogChannel::Trace, "{}", logging::colors::phase_expansion("Phase 2: Expansion"));
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
        if (logger) logger->info(logging::LogChannel::Trace, "{}", logging::colors::phase_rollout("Phase 3: rollout (Simulation)"));
        const_simulation_result_ptr reward = current->rollout();
        iteration_reward = reward ? reward->reward() : 0.0;
        if (logger) 
        {
            auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("rollout from {} → reward: {}", 
                logging::colors::highlight_node(current->name()), reward_str);
        }

        // --- 4. Backpropagation ---
        if (logger) logger->info(logging::LogChannel::Trace, "{}", logging::colors::phase_backprop("Phase 4: Backpropagation"));
        current->backpropagate(reward);
        
        // Iteration summary
        if (logger) 
        {
            const auto reward_str = logging::colors::highlight_reward(std::format("{:.4f}", iteration_reward));
            logger->debug("Iteration {} summary: expanded={}, rollout_reward={}, final_node={}", 
                i + 1, expanded ? "yes" : "no", reward_str, logging::colors::highlight_node(current->name()));
        }
    }

    Dashboard::print(root, logger);
    const auto best_action = root->select_action();
    return best_action;
}

