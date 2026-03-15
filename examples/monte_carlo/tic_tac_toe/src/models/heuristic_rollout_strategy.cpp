#include <tic_tac_toe/models/heuristic_rollout_strategy.h>

using sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::models::Action;


HeuristicRolloutStrategy::HeuristicRolloutStrategy(GameState current_game_state, const logger_ptr& logger)
    : m_current_game_state_(std::move(current_game_state)), m_logger_(logger)
{
}

action_ptr HeuristicRolloutStrategy::select_action(std::vector<action_ptr> actions) const
{
    if (actions.empty())
    {
        return nullptr;
    }

    // TODO: Implement heuristic selection logic
    // For now, just select the first action
    return actions[0];
}
