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
using sophia::monte_carlo::node_ptr;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::rollout_strategy_ptr;
using std::make_shared;
using std::shared_ptr;

TicTacToeFactory::TicTacToeFactory(const const_game_ptr& game, const const_player_ptr& you, logger_ptr logger)
: GenericTreeFactory(std::move(logger))
{
    // Pre-register default strategies
    const auto board = make_shared<Board>(m_logger_);
    GameState dummy_state(game, you, board);
    RegisterStrategy(RolloutStrategyType::Heuristic, make_shared<HeuristicRolloutStrategy>(dummy_state, m_logger_));
    RegisterStrategy(RolloutStrategyType::Random, make_shared<RandomRolloutStrategy>(m_logger_));
    
    // Default active strategy
    SetActiveStrategy(RolloutStrategyType::Heuristic);

    // Set up node generator for root nodes
    SetNodeGenerator([game, you](const std::string& name, const const_factory_ptr& factory, const logger_ptr& logger) {
        auto board = make_shared<Board>(logger);
        const auto game_state = make_shared<GameState>(game, you, board);
        return make_shared<State>(name, game_state, factory, logger);
    });
}
