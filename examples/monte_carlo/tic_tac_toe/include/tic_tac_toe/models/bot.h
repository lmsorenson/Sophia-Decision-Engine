#ifndef BOT_H
#define BOT_H
#include <tic_tac_toe/fwd.h>
#include <tic_tac_toe/models/player.h>
#include <monte_carlo/models/node.h>
#include <tic_tac_toe/observer/observer.h>

#include <memory>

#include "board.h"
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @class Bot
     * @brief A non-human Tic Tac Toe Player
     */
    class Bot : public Player
    {

    public:
        /**
         * @brief Creates a bot with a specific rollout strategy.
         * @param symbol The symbol that the bot places.
         * @param difficulty The skill level of the bot a decimal value from 0 to 1.
         * @param rollout_type The strategy type for simulations (Random or Heuristic).
         * @param logger The logger instance for the bot to use.
         */
        explicit Bot(enums::Symbol symbol, double difficulty,
                    factories::RolloutStrategyType rollout_type,
                    const logger_ptr& logger);

        /**
         * @brief Creates a bot with default heuristic rollout strategy.
         * @param symbol The symbol that the bot places.
         * @param difficulty The skill level of the bot a decimal value from 0 to 1.
         * @param logger The logger instance for the bot to use.
         */
        explicit Bot(enums::Symbol symbol, double difficulty, const logger_ptr& logger);

        /**
         * @brief Initializes the bot by creating its root node.
         */
        void Initialize() override;

        /**
         * @brief Prompts the bot to make its next move.
         * @return A shared pointer to the move made.
         */
        [[nodiscard]] const_position_ptr NextMove() const override;

        /**
         * @brief Updates the player's knowledge of the game.
         * @param message A message indicating the move made.
         * Expecting a 2-letter string consisting of
         * a letter, indicating the row of the placement,
         * followed by a number, indicating the column of the placement.
         * (i.e. 'B2')
         */
        void Update(std::string message) override;

    private:
        mutable node_ptr node_;
        int iterations_;
        factories::RolloutStrategyType m_rollout_type_;
        logger_ptr m_logger_;
    };
}

#endif //BOT_H
