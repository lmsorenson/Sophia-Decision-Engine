#ifndef NODE_BASE_H
#define NODE_BASE_H

#include <monte_carlo/models/node.h>
#include <monte_carlo/factories/tree_factory_interface.h>
#include <monte_carlo/common_aliases.h> // Centralized logger_ptr alias

namespace sophia::monte_carlo::models
{
    /**
     * @brief A template base class for implementing the `Node` interface.
     *
     * This class provides a generic implementation of a node, using templates to support various
     * types of states and changes. It manages the state of the node and provides access to a factory
     * for creating related objects in the tree.
     *
     * @tparam TState The type representing the state of the system (e.g., a board configuration).
     * @tparam TChange The type representing a change that can be applied to a state (e.g., a move).
     */
    template<typename TState, typename TChange>
    class NodeBase : public Node
    {
    public:
        NodeBase(const std::string &name, TState state, const_factory_ptr<TState, TChange> factory, const logger_ptr& logger);

        /// @brief Retrieves the state associated with this node.
        TState GetState() const;

    protected:
        rollout_strategy_ptr RolloutStrategy() const override;

        double interpret_result(const_simulation_result_ptr) const override;

        /// @brief A factory for creating nodes and actions, specific to the game or problem.
        const_factory_ptr<TState, TChange> m_factory_;

        /// @brief The state of the system that this node represents.
        TState m_state_;
    };
}

#include <monte_carlo/models/node_base.tpp>

#endif //NODE_BASE_H
