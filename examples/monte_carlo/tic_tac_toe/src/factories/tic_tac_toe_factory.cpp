#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <tic_tac_toe/models/state.h>
#include <tic_tac_toe/models/move.h>
#include <tic_tac_toe/models/heuristic_rollout_strategy.h>
#include <monte_carlo/models/random_rollout_strategy.h>

#include <utility>
#include <monte_carlo/common_aliases.h> // Centralized aliases

using sophia::monte_carlo::tic_tac_toe::factories::TicTacToeFactory;
using sophia::monte_carlo::tic_tac_toe::models::State;
using sophia::monte_carlo::tic_tac_toe::models::Board;
using sophia::monte_carlo::tic_tac_toe::models::GameState;
using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::tic_tac_toe::models::Move;
using sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy;
using sophia::monte_carlo::models::RandomRolloutStrategy;
using std::make_shared;
using std::shared_ptr;

TicTacToeFactory::TicTacToeFactory(const_player_ptr you, const logger_ptr& logger)
: you_(std::move(you))
, m_logger_(logger)
{
}

void TicTacToeFactory::SetRolloutStrategyType(RolloutStrategyType type)
{
    m_rollout_strategy_type_ = type;
}

sophia::monte_carlo::node_ptr TicTacToeFactory::CreateNode(std::string name) const
{
    auto board = make_shared<Board>(m_logger_);
    const auto game_state = make_shared<GameState>(you_, board);

    return std::static_pointer_cast<models::Node>(make_shared<State>(name, *game_state, shared_from_this(), m_logger_));
}

sophia::monte_carlo::node_ptr TicTacToeFactory::CreateNode(std::string name, GameState game_state) const
{
    return std::static_pointer_cast<models::Node>(make_shared<State>(name, game_state, shared_from_this(), m_logger_));
}

sophia::monte_carlo::action_ptr TicTacToeFactory::CreateAction(node_base_ptr<GameState, Position> node, Position change) const
{
    return make_shared<Move>(node, change, shared_from_this(), m_logger_);
}

sophia::monte_carlo::rollout_strategy_ptr TicTacToeFactory::CreateStrategy() const
{
    if (m_rollout_strategy_type_ == RolloutStrategyType::Heuristic)
    {
        // HeuristicRolloutStrategy will extract the current state from the node being rolled out.
        // We pass a dummy initial state as it will be overridden in select_action.
        auto board = make_shared<Board>(m_logger_);
        GameState dummy_state(you_, board);
        return make_shared<HeuristicRolloutStrategy>(dummy_state, m_logger_);
    }

    return make_shared<RandomRolloutStrategy>(m_logger_);
}