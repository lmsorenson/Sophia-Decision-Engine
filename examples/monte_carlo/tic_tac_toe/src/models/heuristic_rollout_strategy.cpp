#include <tic_tac_toe/models/heuristic_rollout_strategy.h>
#include <tic_tac_toe/models/move.h>
#include <algorithm>
#include <random>
#include <utility>

using sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy;
using sophia::monte_carlo::tic_tac_toe::models::Move;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::models::Action;
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

    // 1. Take winning moves
    const auto winning_moves = m_current_game_state_.GetWinningMoves();
    if (auto winning_action = find_action(actions, winning_moves))
    {
        return winning_action;
    }

    // 2. Block opponent winning moves
    const auto blocking_moves = m_current_game_state_.GetBlockingMoves();
    if (auto blocking_action = find_action(actions, blocking_moves))
    {
        return blocking_action;
    }

    // 3. Prefer center
    static const auto center_pos = std::make_shared<models::Position>(std::make_pair(1, 1));
    if (auto center_action = find_action(actions, {center_pos}))
    {
        return center_action;
    }

    // 4. Prefer corners
    static const std::vector<const_position_ptr> corners = {
        std::make_shared<models::Position>(std::make_pair(0, 0)),
        std::make_shared<models::Position>(std::make_pair(0, 2)),
        std::make_shared<models::Position>(std::make_pair(2, 0)),
        std::make_shared<models::Position>(std::make_pair(2, 2))
    };
    if (auto corner_action = find_action(actions, corners)) {
        return corner_action;
    }

    // 5. Fallback: Random selection from available actions
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, actions.size() - 1);
    return actions[dist(rng)];
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