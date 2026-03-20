#ifndef SOPHIA_MONTE_CARLO_COMMON_ALIASES_H
#define SOPHIA_MONTE_CARLO_COMMON_ALIASES_H

#include <memory>
#include <monte_carlo/fwd.h>

namespace sophia::monte_carlo
{
    using logger_ptr = std::shared_ptr<logging::ILogger>;
    using const_logger_ptr = std::shared_ptr<const logging::ILogger>;
    using node_ptr = std::shared_ptr<models::Node>;
    using const_node_ptr = std::shared_ptr<const models::Node>;
    using actor_ptr = std::shared_ptr<models::Actor>;
    using const_actor_ptr = std::shared_ptr<const models::Actor>;
    using action_ptr = std::shared_ptr<models::Action>;
    using const_action_ptr = std::shared_ptr<const models::Action>;
    using simulation_result_ptr = std::shared_ptr<models::SimulationResult>;
    using const_simulation_result_ptr = std::shared_ptr<const models::SimulationResult>;
    using rollout_strategy_ptr = std::shared_ptr<models::RolloutStrategyInterface>;

    template<typename TState, typename TChange>
    using node_base_ptr = std::shared_ptr<models::NodeBase<TState, TChange>>;

    template<typename TState, typename TChange>
    using node_base_ref = std::weak_ptr<models::NodeBase<TState, TChange>>;

    template<typename TState, typename TChange>
    using const_factory_ptr = std::shared_ptr<const factories::TreeFactoryBase<TState, TChange>>;
}

#endif // SOPHIA_MONTE_CARLO_COMMON_ALIASES_H
