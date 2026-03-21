#include <monte_carlo/factories/generic_tree_factory.h>
#include <monte_carlo/common_aliases.h>

#include <utility>

namespace sophia::monte_carlo::factories
{
#define GENERIC_TREE_FACTORY_TEMPLATE_SIGNATURE template<typename TState, typename TChange, typename TNode, typename TAction>
#define GENERIC_TREE_FACTORY GenericTreeFactory<TState,TChange,TNode,TAction>

GENERIC_TREE_FACTORY_TEMPLATE_SIGNATURE
[[nodiscard]] node_ptr GENERIC_TREE_FACTORY::CreateNode(std::string name, const_state_ptr state) const
{
    auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
    return std::make_shared<TNode>(name, state, factory, this->m_logger_);
}

GENERIC_TREE_FACTORY_TEMPLATE_SIGNATURE
[[nodiscard]] action_ptr GENERIC_TREE_FACTORY::CreateAction(node_base_ptr node, TChange change) const
{
    auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
    return std::make_shared<TAction>(node, change, factory, this->m_logger_);
}

GENERIC_TREE_FACTORY_TEMPLATE_SIGNATURE
[[nodiscard]] action_ptr GENERIC_TREE_FACTORY::CreateAction(node_base_ptr node, TChange change, const const_actor_ptr& actor) const
{
    auto factory = std::static_pointer_cast<const TreeFactoryBase<TState, TChange>>(this->shared_from_this());
    return std::make_shared<TAction>(node, change, actor, factory, this->m_logger_);
}

#undef GENERIC_TREE_FACTORY_TEMPLATE_SIGNATURE
#undef GENERIC_TREE_FACTORY
} // namespace sophia::monte_carlo::models
