#ifndef GENERIC_TREE_FACTORY_H
#define GENERIC_TREE_FACTORY_H

#include <monte_carlo/factories/tree_factory_base.h>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>

namespace sophia::monte_carlo::factories
{
    /**
     * @class GenericTreeFactory
     * @brief A generic implementation of TreeFactoryBase that creates nodes and actions of specified types.
     * 
     * This factory assumes that TNode and TAction have constructors that match the standard
     * signatures used in the Monte Carlo framework.
     * 
     * @tparam TState The state type.
     * @tparam TChange The change type.
     * @tparam TNode The concrete Node type to create.
     * @tparam TAction The concrete Action type to create.
     * @tparam TKey The type used to identify and select rollout strategies.
     */
    template<typename TState, typename TChange, typename TNode, typename TAction, typename TKey = std::string>
    class GenericTreeFactory : public TreeFactoryBase<TState, TChange>
    {
    public:
        using TreeFactoryBase<TState, TChange>::TreeFactoryBase;
        using node_base_ptr = std::shared_ptr<models::NodeBase<TState, TChange>>;
        using const_state_ptr = std::shared_ptr<const TState>;
        using const_factory_ptr = std::shared_ptr<const TreeFactoryBase<TState, TChange>>;
        
        using node_generator = std::function<node_ptr(std::string, const_factory_ptr, const logger_ptr&)>;

        /**
         * @brief Registers a rollout strategy with the factory.
         * @param key The key to identify the strategy.
         * @param strategy The strategy instance.
         */
        void RegisterStrategy(TKey key, rollout_strategy_ptr strategy)
        {
            m_strategies_[key] = std::move(strategy);
        }

        /**
         * @brief Sets the active rollout strategy.
         * @param key The key of the strategy to use.
         */
        void SetActiveStrategy(TKey key)
        {
            m_active_strategy_key_ = key;
        }

        /**
         * @brief Sets the generator function for creating nodes from just a name (e.g., root nodes).
         * @param generator A function that returns a new node given a name.
         */
        void SetNodeGenerator(node_generator generator)
        {
            m_node_generator_ = std::move(generator);
        }

        [[nodiscard]] node_ptr CreateNode(std::string name) const override;

        [[nodiscard]] node_ptr CreateNode(std::string name, const_state_ptr state) const override;

        [[nodiscard]] action_ptr CreateAction(node_base_ptr node, TChange change) const override;

        [[nodiscard]] action_ptr CreateAction(node_base_ptr node, TChange change, const const_actor_ptr& actor) const override;

        [[nodiscard]] rollout_strategy_ptr CreateStrategy() const override;

    protected:
        std::map<TKey, rollout_strategy_ptr> m_strategies_;
        TKey m_active_strategy_key_{};
        node_generator m_node_generator_;
    };
}

#include <monte_carlo/factories/generic_tree_factory.tpp>

#endif //GENERIC_TREE_FACTORY_H
