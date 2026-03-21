#ifndef NODE_H
#define NODE_H

#include <monte_carlo/models/rollout_strategy_interface.h>
#include <vector>
#include <memory>
#include <monte_carlo/common_aliases.h>
#include <monte_carlo/fwd.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Represents a node in the Monte Carlo Search Tree. Each node corresponds to a state in the problem space.
     *
     * The Node class is central to the MCTS algorithm. It stores statistics about the state it represents,
     * such as the number of visits and the total reward. It also provides methods for the four main phases of MCTS:
     * selection, expansion, simulation (rollout), and backpropagation.
     */
    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        explicit Node(std::string name, const logger_ptr& logger);
        virtual ~Node() = default;

        /// @brief Sets the parent action that leads to this node.
        void set_parent(const action_ptr& action);

        /**
         * @brief Selects the best child action based on the UCB1 formula. (Selection Phase)
         * This method is part of the selection phase of MCTS, where the tree is traversed from the
         * root to a leaf node by selecting the most promising actions.
         */
        [[nodiscard]] action_ptr select_best_action() const;

        /**
         * @brief Expands the tree by creating a new child node from an untried action. (Expansion Phase)
         * If the current node is not a terminal state and has untried actions, this method will
         * create a new child node for one of those actions.
         */
        node_ptr expand();

        /**
         * @brief Simulates a path from the current node to a terminal state. (Simulation Phase)
         * Also known as a rollout, this phase estimates the value of the current node by
         * simulating a path to a terminal state, usually with a simple and fast policy.
         * @return The reward obtained from the simulation.
         */
        const_simulation_result_ptr rollout();

        /**
         * @brief Updates the statistics of the nodes from the current node up to the root. (Backpropagation Phase)
         * After a simulation, the result (reward) is propagated back up the tree, updating the
         * visit counts and total rewards of the nodes along the path.
         * @param reward The reward obtained from the simulation.
         */
        void backpropagate(const const_simulation_result_ptr &reward);

        /// @brief Returns the name of the node for identification.
        [[nodiscard]] std::string name() const;

        /**
         * @brief Calculates the Upper Confidence Bound (UCB1) for this node..
         * This is used in the selection phase to balance exploration and exploitation.
         * @param c The exploration parameter.
         * @return The UCB1 value.
         */
        [[nodiscard]] double upper_confidence_bound(int c) const;

        /// @brief Checks if this node is a leaf node (i.e., has no children).
        [[nodiscard]] bool is_leaf_node() const;

        /// @brief Checks if this node has been visited during the search.
        [[nodiscard]] bool has_been_sampled() const;

        /// @brief Gets the number of times this node has been visited.
        [[nodiscard]] int visit_count() const;

        /// @brief Gets the total reward accumulated at this node.
        [[nodiscard]] double total_reward() const;

        /// @brief Pure virtual function to check if the node represents a terminal state in the problem space.
        [[nodiscard]] virtual bool is_terminal_state() const = 0;

        /// @brief Pure virtual function to get the value or outcome of the terminal state (e.g., a score, win/loss outcome, etc.).
        [[nodiscard]] virtual const_simulation_result_ptr value() const = 0;

        /// @brief Selects a specific action by its name.
        virtual action_ptr select_action(std::string action_name) = 0;

        /// @brief Selects an action, typically used for the simulation phase.
        virtual action_ptr select_action();

        /// @brief Prints a representation of the node's state.
        virtual void print() const = 0;

        /// @brief Pure virtual function to generate the list of all possible actions from this node's state.
        [[nodiscard]] virtual std::vector<action_ptr> get_available_actions() = 0;

        /// @brief Pure virtual function to get the list of all possible actions from this node's state.
        [[nodiscard]] virtual std::vector<action_ptr> children() const = 0;

        /// @brief A weak pointer to the parent action of this node.
        std::weak_ptr<Action> m_parent_action_;

        /// @brief A vector of shared pointers to the child actions of this node.
        std::vector<action_ptr> m_child_action_;

        /// @brief The number of times this node has been visited in the search.
        unsigned long m_visit_count_ = 0;

        /// @brief The total reward accumulated from simulations passing through this node.
        double m_total_reward_ = 0;

    protected:
        logger_ptr m_logger_;

        virtual double interpret_result(const_simulation_result_ptr) const = 0;

    private:
        /// @brief Pure virtual function to get the rollout strategy to be used for the simulation phase.
        virtual rollout_strategy_ptr rollout_strategy() const = 0;

        std::string m_name_;
    };
}

#endif //NODE_H