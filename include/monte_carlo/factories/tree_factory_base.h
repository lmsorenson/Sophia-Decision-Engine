#ifndef TREE_FACTORY_INTERFACE_H
#define TREE_FACTORY_INTERFACE_H

#include <memory>
#include <string>
#include <monte_carlo/fwd.h>
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::factories
{
    using models::NodeBase;

    template<typename TState, typename TChange>
    class TreeFactoryBase : public std::enable_shared_from_this<TreeFactoryBase<TState, TChange>>
    {
    protected:
        using state_ptr = std::shared_ptr<TState>;

    public:
        explicit TreeFactoryBase(logger_ptr  logger);
        virtual ~TreeFactoryBase() = default;

        /**
         * Creates a new Node.
         * @param name the name of the new Node being created.
         * @returns a shared pointer to a Node.
         */
        [[nodiscard]] virtual node_ptr CreateNode(std::string name) const = 0;

        /**
         * Creates a new Node.
         * @param name the name of the new Node being created.
         * @param state the state represented by the Node being created.
         * @returns a shared pointer to a Node.
         */
        [[nodiscard]] virtual node_ptr CreateNode(std::string name, TState state) const = 0;

        /**
         * Creates a new Action.
         * @param node the source node for the action being created.
         * @param change the change being applied to the source node.
         * @param actor the actor that performed the action.
         * @returns a shared pointer to a Node.
         */
        [[nodiscard]] virtual action_ptr CreateAction(node_base_ptr<TState, TChange> node, TChange change, const const_actor_ptr& actor) const = 0;

        /**
         * Creates a new Action.
         * @param node the source node for the action being created.
         * @param change the change being applied to the source node.
         * @returns a shared pointer to a Node.
         */
        [[nodiscard]] virtual action_ptr CreateAction(node_base_ptr<TState, TChange> node, TChange change) const = 0;

        /**
         * Creates a new Strategy.
         * @returns a shared pointer to a rollout strategy.
         */
        [[nodiscard]] virtual rollout_strategy_ptr CreateStrategy() const = 0;

    protected:
        logger_ptr m_logger_;
    };
}

#include <monte_carlo/factories/tree_factory_base.tpp>

#endif //TREE_FACTORY_INTERFACE_H
