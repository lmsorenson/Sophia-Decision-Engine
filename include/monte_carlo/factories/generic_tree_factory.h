#ifndef GENERIC_TREE_FACTORY_H
#define GENERIC_TREE_FACTORY_H

#include <monte_carlo/factories/tree_factory_base.h>
#include <string>
#include <memory>
#include <vector>

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
     */
    template<typename TState, typename TChange, typename TNode, typename TAction>
    class GenericTreeFactory : public TreeFactoryBase<TState, TChange>
    {
    public:
        using TreeFactoryBase<TState, TChange>::TreeFactoryBase;
        using node_base_ptr = std::shared_ptr<models::NodeBase<TState, TChange>>;
        using const_state_ptr = std::shared_ptr<const TState>;
        using const_factory_ptr = std::shared_ptr<const TreeFactoryBase<TState, TChange>>;

        [[nodiscard]] node_ptr CreateNode(std::string name, const_state_ptr state) const override
        {
            auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
            return std::make_shared<TNode>(name, state, factory, this->m_logger_);
        }

        [[nodiscard]] action_ptr CreateAction(node_base_ptr node, TChange change) const override
        {
            auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
            return std::make_shared<TAction>(node, change, factory, this->m_logger_);
        }

        [[nodiscard]] action_ptr CreateAction(node_base_ptr node, TChange change, const const_actor_ptr& actor) const override
        {
            auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
            return std::make_shared<TAction>(node, change, actor, factory, this->m_logger_);
        }

        // CreateStrategy and the default CreateNode(name) still need to be implemented or overridden
        // as they are often problem-specific.
    };
}

#endif //GENERIC_TREE_FACTORY_H
