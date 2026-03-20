#ifndef SOPHIA_MONTE_CARLO_MODELS_ACTION_BASE_TPP
#define SOPHIA_MONTE_CARLO_MODELS_ACTION_BASE_TPP

#include <monte_carlo/models/action_base.h>
#include <monte_carlo/common_aliases.h> // Centralized aliases

namespace sophia::monte_carlo::models
{

template<typename TState, typename TChange>
ActionBase<TState, TChange>::ActionBase(const node_base_ptr<TState, TChange> &state, TChange change, const_factory_ptr<TState, TChange> factory, const logger_ptr& logger)
    : Action()
    , m_factory_(factory)
    , m_logger_(logger)
    , m_source_(state)
    , m_change_(change)
{
}

template<typename TState, typename TChange>
ActionBase<TState, TChange>::ActionBase(const node_base_ptr<TState, TChange> &state, TChange change, const const_actor_ptr& actor, const_factory_ptr<TState, TChange> factory, const logger_ptr& logger)
    : Action()
    , m_factory_(factory)
    , m_logger_(logger)
    , m_source_(state)
    , m_actor_(actor)
    , m_change_(change)
{
}

template<typename TState, typename TChange>
node_ptr ActionBase<TState, TChange>::source() const
{
    return m_source_.lock();
}

template<typename TState, typename TChange>
node_ptr ActionBase<TState, TChange>::target() const
{
    return m_target_;
}

template<typename TState, typename TChange>
const_actor_ptr ActionBase<TState, TChange>::actor() const
{
    return m_actor_;
}

} // namespace sophia::monte_carlo::models

#endif // SOPHIA_MONTE_CARLO_MODELS_ACTION_BASE_TPP
