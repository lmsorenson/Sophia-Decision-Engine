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
using sophia::monte_carlo::node_ptr;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::rollout_strategy_ptr;
using sophia::monte_carlo::models::RandomRolloutStrategy;
using std::make_shared;
using std::shared_ptr;

TicTacToeFactory::TicTacToeFactory(const_game_ptr game, const_player_ptr you, logger_ptr logger)
: TreeFactoryBase(std::move(logger))
, m_game_(std::move(game))
, m_you_(std::move(you))
{
}

void TicTacToeFactory::SetRolloutStrategyType(RolloutStrategyType type)
{
    m_rollout_strategy_type_ = type;
}

node_ptr TicTacToeFactory::CreateNode(std::string name) const
{
    auto board = make_shared<Board>(m_logger_);
    const auto game_state = make_shared<GameState>(m_game_, m_you_, board);

    return make_shared<State>(name, *game_state, shared_from_this(), m_logger_);
}

node_ptr TicTacToeFactory::CreateNode(std::string name, GameState game_state) const
{
    return make_shared<State>(name, game_state, shared_from_this(), m_logger_);
}

action_ptr TicTacToeFactory::CreateAction(node_base_ptr<GameState, Position> node, Position change) const
{
    return make_shared<Move>(node, change, shared_from_this(), m_logger_);
}

action_ptr TicTacToeFactory::CreateAction(node_base_ptr<GameState, Position> node, Position change, const const_actor_ptr& actor) const
{
    return make_shared<Move>(node, change, actor, shared_from_this(), m_logger_);
}

rollout_strategy_ptr TicTacToeFactory::CreateStrategy() const
{
    if (m_rollout_strategy_type_ == RolloutStrategyType::Heuristic)
    {
        const auto board = make_shared<Board>(m_logger_);
        GameState dummy_state(m_game_, m_you_, board);
        return make_shared<HeuristicRolloutStrategy>(dummy_state, m_logger_);
    }

    return make_shared<RandomRolloutStrategy>(m_logger_);
}