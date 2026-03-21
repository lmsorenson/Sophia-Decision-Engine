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
    class TicTacToeFactory : public monte_carlo::factories::GenericTreeFactory<models::GameState, models::Position, models::State, models::Move>
    {
    public:
        using GenericTreeFactory::CreateNode;
        using GenericTreeFactory::CreateAction;
        /**
         * @brief Creates an instance of TicTacToeFactory
         * @param game The game being played.
         * @param you a shared pointer to the player that owns the simulation.
         * @param logger the logger for the factory to use.
         */
        explicit TicTacToeFactory(const_game_ptr game, const_player_ptr you, logger_ptr logger);
        ~TicTacToeFactory() override = default;

        /**
         * @brief Sets the rollout strategy type to be created by the factory.
         * @param type The strategy type.
         */
        void SetRolloutStrategyType(RolloutStrategyType type);

        /**
         * @brief Creates a new Node.
         * @param name the name of the new Node being created.
         * @returns a shared pointer to a Node
         */
        [[nodiscard]] node_ptr CreateNode(std::string name) const override;

        /**
         * @brief Creates a new Strategy.
         * @returns a shared pointer to a rollout strategy.
         */
        [[nodiscard]] rollout_strategy_ptr CreateStrategy() const override;

    private:
        const_game_ptr m_game_;
        const_player_ptr m_you_;
        RolloutStrategyType m_rollout_strategy_type_ = RolloutStrategyType::Heuristic;
    };
}

#endif //TIC_TAC_TOE_FACTORY_H
