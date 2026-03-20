#ifndef SOPHIA_MONTE_CARLO_MODELS_ROLLOUT_STRATEGY_INTERFACE_H
#define SOPHIA_MONTE_CARLO_MODELS_ROLLOUT_STRATEGY_INTERFACE_H

#include <memory>
#include <vector>
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Interface for defining a rollout strategy in the Monte Carlo Tree Search (MCTS) algorithm.
     *
     * A rollout (or simulation) is a traversal from a given node to a terminal state of the problem space.
     * The rollout strategy defines how actions are selected during this simulation phase.
     * Different strategies can be implemented to balance exploration and exploitation.
     */
    class RolloutStrategyInterface
    {
    public:
        RolloutStrategyInterface() = default;
        virtual ~RolloutStrategyInterface() = default;

        /**
         * @brief Selects an action from a vector of available actions based on the implemented strategy.
         * @param actions A vector of shared pointers to the available actions.
         * @return A shared pointer to the selected action.
         */
        [[nodiscard]] virtual action_ptr select_action(std::vector<action_ptr> actions) const = 0;
    };
}


#endif // SOPHIA_MONTE_CARLO_MODELS_ROLLOUT_STRATEGY_INTERFACE_H
