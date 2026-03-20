#include <monte_carlo/models/random_rollout_strategy.h>
#include <random>
#include <monte_carlo/models/action.h>
#include <monte_carlo/common_aliases.h>
#include <logging/ilogger.h>

using sophia::monte_carlo::models::RandomRolloutStrategy;
using sophia::monte_carlo::action_ptr;
using std::shared_ptr;
using std::vector;

RandomRolloutStrategy::RandomRolloutStrategy(const logger_ptr& logger)
: m_logger_(logger)
{
}

action_ptr RandomRolloutStrategy::select_action(std::vector<action_ptr> actions) const
{
    if (actions.empty())
    {
        return nullptr;
    }

    // get random action.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, actions.size() - 1);
    const auto& random_action = actions[dist(gen)];

    if (m_logger_) m_logger_->debug("rollout selection: {}", random_action->name());

    return random_action;
}


