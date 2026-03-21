#ifndef TIC_TAC_TOE_FACTORY_H
#define TIC_TAC_TOE_FACTORY_H

#include <tic_tac_toe/models/game_state.h>
#include <tic_tac_toe/models/position.h>
#include <tic_tac_toe/models/state.h>
#include <tic_tac_toe/models/move.h>
#include <monte_carlo/factories/generic_tree_factory.h>

namespace sophia::monte_carlo::tic_tac_toe::factories
{
    /**
     * @class TicTacToeFactory
     * @brief Creates simulation nodes and actions for a Tic Tac Toe game.
     *
     * Example:
     * @code
     * std::shared_ptr<models::const_player_ptr> you;
     * auto f = std::make_shared<TicTacToeFactory>(you);
     * auto node = f->CreateNode();
     * @endcode
     */
    class TicTacToeFactory
        : public monte_carlo::factories::GenericTreeFactory<
            models::GameState,
            models::Position,
            models::State,
            models::Move,
            RolloutStrategyType>
    {
    public:
        /**
         * @brief Creates an instance of TicTacToeFactory
         * @param game The game being played.
         * @param you a shared pointer to the player that owns the simulation.
         * @param logger the logger for the factory to use.
         */
        explicit TicTacToeFactory(const const_game_ptr& game, const const_player_ptr& you, logger_ptr logger);
        ~TicTacToeFactory() override = default;
    };
}

#endif //TIC_TAC_TOE_FACTORY_H
