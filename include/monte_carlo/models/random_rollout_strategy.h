#ifndef SOPHIA_MONTE_CARLO_MODELS_RANDOM_ROLLOUT_STRATEGY_H
#define SOPHIA_MONTE_CARLO_MODELS_RANDOM_ROLLOUT_STRATEGY_H

#include "rollout_strategy_interface.h"
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    class Action;

    /**
     * @brief A concrete implementation of the RolloutStrategyInterface that selects an action randomly.
     *
     * This strategy provides a simple and fast way to run simulations by choosing actions
     * uniformly at random from the list of available options. It is often used as a default
     * or baseline strategy in MCTS.
     */
    class RandomRolloutStrategy final : public RolloutStrategyInterface
    {
    public:
        /**
         * @brief Constructs a RandomRolloutStrategy.
         * @param logger The logger instance for the strategy to use.
         */
        explicit RandomRolloutStrategy(const logger_ptr& logger);

        /**
         * @brief Selects a random action from a vector of available actions.
         * @param actions A vector of shared pointers to the available actions.
         * @return A shared pointer to the randomly selected action.
         */
        [[nodiscard]] action_ptr select_action(std::vector<action_ptr> actions) const override;

    protected:
        logger_ptr m_logger_; // Member to hold the logger instance
    };
}

#endif // SOPHIA_MONTE_CARLO_MODELS_RANDOM_ROLLOUT_STRATEGY_H
