#include <monte_carlo/models/node_base.h>
#include <monte_carlo/models/simulation_result.h>
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{

template<typename TState, typename TChange>
NodeBase<TState, TChange>::NodeBase(const std::string &name, TState state, sophia::monte_carlo::const_factory_ptr<TState, TChange> factory, const sophia::monte_carlo::logger_ptr& logger)
    : Node(name, logger)
    , m_state_(state)
    , m_factory_(factory)
{
}

template<typename TState, typename TChange>
TState NodeBase<TState, TChange>::GetState() const
{
    return m_state_;
}

template<typename TState, typename TChange>
rollout_strategy_ptr NodeBase<TState, TChange>::RolloutStrategy() const
{
    return m_factory_->CreateStrategy();
}

template<typename TState, typename TChange>
double NodeBase<TState, TChange>::interpret_result(const const_simulation_result_ptr result) const
{
    if (!result) return 0.0;
    return result->Reward();
}

} // namespace sophia::monte_carlo::models
