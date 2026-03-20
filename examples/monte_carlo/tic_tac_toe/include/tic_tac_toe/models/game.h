#ifndef GAME_H
#define GAME_H
#include <tic_tac_toe/models/board.h>
#include <tic_tac_toe/observer/subject.h>
#include <memory>
#include <stdexcept>
#include <monte_carlo/common_aliases.h> // Centralized logger_ptr alias

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @class Game
     * @brief A Tic Tac Toe game.
     */
    class Game : observer::Subject, public std::enable_shared_from_this<Game>
    {
    public:
        /**
         * @brief Constructs a new Game with default settings.
         * @param logger The logger instance for the game to use.
         */
        explicit Game(const logger_ptr& logger);
        ~Game();

        /**
         * @brief Assigns a particular type of player to a symbol.
         * @tparam TPlayer The type of player to be assigned.  (Probably a Human or a Bot)
         * @tparam Args Constructor arguments for the Player.
         * @param symbol The symbol in which the new player will occupy.
         * @param args The constructor argument values for the Player.
         * @throws invalid_argument if the Symbol is not valid.
         */
        template<class TPlayer, typename... Args>
        void Assign(enums::Symbol symbol, Args... args);

        /**
         * @brief Is the game over?
         * @return A boolean value: true if the game is over, false if it is not.
         */
        [[nodiscard]] bool game_over() const;

        /**
         * @brief Gets the current active player.
         * @return A shared pointer to the active player of the game.
         */
        [[nodiscard]] const_player_ptr active_player() const;

        /**
         * @brief Gets the current active player.
         * @return A shared pointer to the active player of the game.
         */
        [[nodiscard]] const_player_ptr get_player(enums::Symbol symbol) const;

        /**
         * @brief Applies a move to the Tic Tac Toe game.
         * @param move The move being applied.
         */
        void accept_move(Position move);

        /**
         * @brief Prints the Tic Tac Toe game to the console.
         */
        void print() const;

    private:
        /**
         * @brief The player controlling the X positions.
         */
        player_ptr x_ = nullptr;

        /**
         * @brief The player controlling the Y positions.
         */
        player_ptr o_ = nullptr;

        /**
         * @brief A list of boards.  A board represents a state of play.
         */
        std::vector<const_board_ptr> game_states_;

        /**
         * @brief The logger instance for the game.
         */
        logger_ptr m_logger_;
    };

    template<class TPlayer, typename... Args>
    void Game::Assign(enums::Symbol symbol, Args ... args)
    {
        player_ptr* target_player = nullptr;
        switch (symbol)
        {
            case enums::Symbol::X:
                target_player = &x_;
                break;
            case enums::Symbol::O:
                target_player = &o_;
                break;
            default: throw std::invalid_argument("Invalid symbol");
        }

        *target_player = std::make_shared<TPlayer>(symbol, args..., m_logger_);
        (*target_player)->Initialize(shared_from_this());
        add_observer(*target_player);
    }
}


#endif //GAME_H
