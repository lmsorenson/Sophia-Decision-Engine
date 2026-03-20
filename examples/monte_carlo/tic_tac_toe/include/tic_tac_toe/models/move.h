#ifndef SOPHIA_TIC_TAC_TOE_MODELS_MOVE_H
#define SOPHIA_TIC_TAC_TOE_MODELS_MOVE_H

#include <monte_carlo/models/action_base.h>
#include <monte_carlo/factories/tree_factory_interface.h>

#include <tic_tac_toe/models/game_state.h>
#include <tic_tac_toe/models/position.h>
#include <monte_carlo/common_aliases.h>
#include <monte_carlo/fwd.h>

namespace sophia::monte_carlo::tic_tac_toe::models
{
    using monte_carlo::models::Node;
    using monte_carlo::factories::TreeFactoryBase;
    using monte_carlo::models::ActionBase;

    /**
     * @class Move
     * @brief A move made on the Tic Tac Toe board.
     */
    class Move : public ActionBase<GameState, Position>
    {
    public:
        /**
         * @brief Creates an instance of a Move.
         * @param source A shared pointer to the source Node.
         * @param change The change being applied to the game.
         * @param actor The actor that performed the move.
         * @param factory A shared pointer to the Tree Factory.
         */
        explicit Move(const node_base_ptr<GameState, Position> &source,
            Position change,
            const const_actor_ptr& actor,
            const_factory_ptr<GameState, Position> factory,
            const logger_ptr& logger);

        /**
         * @brief Creates an instance of a Move.
         * @param source A shared pointer to the source Node.
         * @param change The change being applied to the game.
         * @param factory A shared pointer to the Tree Factory.
         */
        explicit Move(const node_base_ptr<GameState, Position> &source,
            Position change,
            const_factory_ptr<GameState, Position> factory,
            const logger_ptr& logger);

        /**
         * @brief The name of the move.
         * @return The name of the move.
         */
        std::string name() const override;

        /**
         * @brief Gets the position change associated with this move.
         * @return The position.
         */
        [[nodiscard]] Position Change() const;

        /**
         * Generates the outcome of the move.
         */
        void generate() override;
    };
}

#endif // SOPHIA_TIC_TAC_TOE_MODELS_MOVE_H
