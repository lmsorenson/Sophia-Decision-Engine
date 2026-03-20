#ifndef SOPHIA_TIC_TAC_TOE_MODELS_HEURISTIC_ROLLOUT_STRATEGY_H
#define SOPHIA_TIC_TAC_TOE_MODELS_HEURISTIC_ROLLOUT_STRATEGY_H

#include <tic_tac_toe/models/game_state.h>
#include <monte_carlo/models/rollout_strategy_interface.h>
#include <monte_carlo/common_aliases.h>

#include <memory>
#include <vector>

namespace sophia::monte_carlo::tic_tac_toe::models
{

    /**
     * @brief A heuristic rollout strategy for Tic-Tac-Toe.
     *
     * This strategy attempts to select the best action based on simple heuristic rules
     * to guide the Monte Carlo simulations towards more promising outcomes.
     */
    class HeuristicRolloutStrategy : public monte_carlo::models::RolloutStrategyInterface
    {
    public:
        /**
         * @brief Constructs a HeuristicRolloutStrategy.
         * @param current_game_state The current game state from which the rollout will start.
         * @param logger The logger instance.
         */
        explicit HeuristicRolloutStrategy(GameState current_game_state, logger_ptr logger);

        /**
         * @brief Selects an action from a vector of available actions based on heuristic rules.
         * @param actions A vector of shared pointers to the available actions. These are expected to be TicTacToe Move objects.
         * @return A shared pointer to the selected action (Move).
         */
        [[nodiscard]] action_ptr select_action(std::vector<action_ptr> actions) const override;

    private:
        static action_ptr find_action(
            const std::vector<action_ptr> &actions,
            const std::vector<const_position_ptr>& target_positions);

        GameState m_current_game_state_;
        logger_ptr m_logger_;
    };
} // namespace sophia::monte_carlo::tic_tac_toe::models

#endif // SOPHIA_TIC_TAC_TOE_MODELS_HEURISTIC_ROLLOUT_STRATEGY_H
