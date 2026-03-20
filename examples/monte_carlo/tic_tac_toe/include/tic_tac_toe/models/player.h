#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <tic_tac_toe/enums/symbol.h>
#include <tic_tac_toe/observer/observer.h>
#include <monte_carlo/common_aliases.h>
#include <monte_carlo/models/actor.h>

#include "common_aliases.h"

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @class Player
     * @brief A Player in a Tic Tac Toe Game
     */
    class Player : public monte_carlo::models::Actor, public std::enable_shared_from_this<Player>, public observer::Observer
    {
    public:
        explicit Player(enums::Symbol symbol, const logger_ptr& logger);
        virtual ~Player() = default;

        /**
         * @brief Initializes the player.
         * @param game A pointer to the game.
         */
        virtual void Initialize(const_game_ptr game) {};

        /**
         * @brief The Symbol used by the Player.
         * @return
         */
        [[nodiscard]] enums::Symbol symbol() const;

        /**
         * @brief Prompts the Player to make its next move.
         * @return A shared pointer to the move made.
         */
        [[nodiscard]] virtual const_position_ptr NextMove() const = 0;

        /**
         * @brief Assigns a value of the board state from the perspective of this Player.
         * @param board The board information for the current game.
         * @return A double value that represents the score of the game from the
         * perspective of the Player.
         */
        [[nodiscard]] double Value(const Board &board) const;

    protected:
        enums::Symbol m_player_symbol_ = enums::Symbol::None;
        logger_ptr m_logger_;
    };
}

#endif //PLAYER_H
