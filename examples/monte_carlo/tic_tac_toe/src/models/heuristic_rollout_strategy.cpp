#include <tic_tac_toe/models/heuristic_rollout_strategy.h>
#include <tic_tac_toe/models/move.h>
#include <monte_carlo/models/node_base.h>
#include <algorithm>
#include <random>
#include <utility>

using sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy;
using sophia::monte_carlo::tic_tac_toe::models::Move;
using sophia::monte_carlo::tic_tac_toe::models::GameState;
using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::models::Action;
using sophia::monte_carlo::models::NodeBase;
using sophia::monte_carlo::tic_tac_toe::const_position_ptr;

HeuristicRolloutStrategy::HeuristicRolloutStrategy(GameState current_game_state, logger_ptr  logger)
    : m_current_game_state_(std::move(current_game_state)), m_logger_(std::move(logger))
{
}

action_ptr HeuristicRolloutStrategy::select_action(std::vector<action_ptr> actions) const
{
    if (actions.empty())
    {
        return nullptr;
    }

    // Attempt to get the latest state from the actions themselves.
    // This allows the strategy to be used in multi-step rollouts where the state changes.
    GameState state = m_current_game_state_;
    if (auto node = std::dynamic_pointer_cast<NodeBase<GameState, Position>>(actions[0]->source()))
    {
        state = node->get_state();
    }

    // 1. Take winning moves
    const auto winning_moves = state.GetWinningMoves();
    if (auto winning_action = find_action(actions, winning_moves))
    {
        if (m_logger_) m_logger_->trace("HeuristicRollout: Choosing winning move '{}'.", winning_action->name());
        return winning_action;
    }

    // 2. Block opponent winning moves
    const auto blocking_moves = state.GetBlockingMoves();
    if (auto blocking_action = find_action(actions, blocking_moves))
    {
        if (m_logger_) m_logger_->trace("HeuristicRollout: Choosing blocking move '{}'.", blocking_action->name());
        return blocking_action;
    }

    // 3. Prefer center
    // static const auto center_pos = std::make_shared<models::Position>(std::make_pair(1, 1));
    // if (auto center_action = find_action(actions, {center_pos}))
    // {
    //     if (m_logger_) m_logger_->trace("HeuristicRollout: Choosing center '{}'.", center_action->name());
    //     return center_action;
    // }

    // // 4. Prefer corners
    // static const std::vector<const_position_ptr> corners = {
    //     std::make_shared<models::Position>(std::make_pair(0, 0)),
    //     std::make_shared<models::Position>(std::make_pair(0, 2)),
    //     std::make_shared<models::Position>(std::make_pair(2, 0)),
    //     std::make_shared<models::Position>(std::make_pair(2, 2))
    // };
    // if (auto corner_action = find_action(actions, corners)) {
    //     if (m_logger_) m_logger_->trace("HeuristicRollout: Choosing corner '{}'.", corner_action->name());
    //     return corner_action;
    // }

    // 5. Fallback: Random selection from available actions
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, actions.size() - 1);
    auto random_action = actions[dist(rng)];
    if (m_logger_) m_logger_->trace("HeuristicRollout: Choosing random move '{}'.", random_action->name());
    return random_action;
}

action_ptr HeuristicRolloutStrategy::find_action(
    const std::vector<action_ptr> &actions,
    const std::vector<const_position_ptr>& target_positions)
{
    for (const auto& target_pos : target_positions)
    {
        for (const auto& action : actions)
        {
            if (const auto move = std::dynamic_pointer_cast<Move>(action))
            {
                if (move->Change().Coordinates() == target_pos->Coordinates())
                {
                    return action;
                }
            }
        }
    }
    return nullptr;
}