#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Represents an action that can be taken from a specific state (Node) in the search tree.
     *
     * An action is a transition from a source node to a target node. It represents a move, a decision,
     * or any other change in the state of the system being modeled.
     */
    class Action : public std::enable_shared_from_this<Action>
    {
    public:
        Action() = default;
        virtual ~Action() = default;

        /// @brief Get the name of the action for identification purposes.
        virtual std::string name() const = 0;

        /**
         * @brief Calculates the Upper Confidence Bound (UCB1) for this action.
         *
         * UCB1 is a formula used to balance exploration and exploitation in MCTS.
         * It's calculated based on the action's value and the number of times it has been visited.
         *
         * @param c The exploration parameter, which controls the trade-off between exploration and exploitation.
         * @return The UCB1 value for this action.
         */
        [[nodiscard]] double upper_confidence_bound(int c) const;

        /// @brief Generates the target node that results from taking this action.
        virtual void generate() = 0;

        /// @brief Retrieves the source node from which this action originates.
        [[nodiscard]] virtual node_ptr source() const = 0;

        /// @brief Retrieves the target node that results from this action.
        [[nodiscard]] virtual node_ptr target() const = 0;

        /// @brief Retrieves the actor that performed this action.
        [[nodiscard]] virtual const_actor_ptr actor() const = 0;
    };
}

#endif //ACTION_H
