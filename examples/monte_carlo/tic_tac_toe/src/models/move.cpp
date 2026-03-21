#include <tic_tac_toe/models/move.h>

#include <utility>
#include <format>
#include <monte_carlo/factories/tree_factory_base.h>
#include <monte_carlo/models/node_base.h>
#include <tic_tac_toe/enums/symbol.h>

using sophia::monte_carlo::tic_tac_toe::models::Move;
using sophia::monte_carlo::tic_tac_toe::enums::TileStateToString;
using sophia::monte_carlo::tic_tac_toe::models::GameState;
using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::models::Action;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::factories::TreeFactoryBase;
using std::shared_ptr;

Move::Move(
    const node_base_ptr<GameState, Position> &source,
    const Position change,
    const_factory_ptr<GameState, Position> factory,
    const logger_ptr& logger)
: ActionBase(source, change, std::move(factory), logger)
{

}

Move::Move(
    const node_base_ptr<GameState, Position> &source,
    const Position change,
    const const_actor_ptr& actor,
    const_factory_ptr<GameState, Position> factory,
    const logger_ptr& logger)
: ActionBase(source, change, actor, std::move(factory), logger)
{
}

std::string Move::name() const
{
    return m_change_.name();
}

Position Move::Change() const
{
    return m_change_;
}

void Move::generate()
{
    if (const auto source = m_source_.lock())
    {
        const auto game_state = source->get_state();

        const auto new_state = game_state.apply_move(m_change_);

        const std::string node_name = std::format("{}{}_T{}", TileStateToString(m_change_.State()), m_change_.name(), new_state->GetTurnNumber());

        m_target_ = m_factory_->CreateNode(node_name, *new_state);
    }
}
