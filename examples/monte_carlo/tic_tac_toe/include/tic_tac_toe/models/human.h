#ifndef SOPHIA_TIC_TAC_TOE_MODELS_HUMAN_H
#define SOPHIA_TIC_TAC_TOE_MODELS_HUMAN_H
#include <tic_tac_toe/models/player.h>
#include <tic_tac_toe/models/board.h>
#include <monte_carlo/common_aliases.h>
#include <functional>

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @class Human
     * @brief A human Tic Tac Toe Player
     */
    class Human : public Player
    {
    public:
        /**
         * @brief Creates an instance of a Human Player.
         * @param symbol The Symbol that this Player places.
         * @param logger The logger instance for the player to use.
         * @param get_move_input_callback A callback function to get move input from the user.
         */
        explicit Human(enums::Symbol symbol, std::function<std::string()> get_move_input_callback, const logger_ptr& logger);

        /**
         * @brief Prompts the Human to make its next move.
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
        logger_ptr m_logger_; // Member to hold the logger instance
        std::function<std::string()> get_move_input_callback_; // Member to hold the input callback
    };
}

#endif // SOPHIA_TIC_TAC_TOE_MODELS_HUMAN_H
