#include <monte_carlo/models/node.h>
#include <monte_carlo/models/rollout_strategy_interface.h>
#include <monte_carlo/factories/tree_factory_base.h>
#include <logging/colors.h>
#include <logging/ilogger.h>
#include <cmath>
#include <utility>
#include <sstream>
#include <limits>
#include <format>
#include <monte_carlo/models/action.h>
#include <monte_carlo/common_aliases.h>

#include "monte_carlo/models/simulation_result.h"

using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::factories::TreeFactoryBase;
using sophia::monte_carlo::node_ptr;
using sophia::monte_carlo::action_ptr;
using sophia::monte_carlo::const_simulation_result_ptr;
using std::string;
using std::shared_ptr;
using std::vector;

Node::Node(string name, const logger_ptr& logger)
    : m_name_(std::move(name))
    , m_logger_(logger)
{
}

void Node::set_parent(const action_ptr& action)
{
    m_parent_action_ = action;
}

action_ptr Node::select_best_action() const
{
    if (m_child_action_.empty())
    {
        if (m_logger_) m_logger_->warn("Node '{}' has no children to select best action from.", name());
        return nullptr;
    }

    double best_score = -std::numeric_limits<double>::infinity();
    action_ptr best_child = nullptr;

    if (m_logger_)
    {
        m_logger_->trace("Evaluating actions from {}:", logging::colors::highlight_node(name()));
        for (const auto& child : m_child_action_)
        {
            const double current_score = child->upper_confidence_bound(2);
            if (auto target = child->target())
            {
                const double avg_reward = target->visit_count() > 0 ? target->total_reward() / target->visit_count() : 0.0;
                const std::string avg_str = target->visit_count() > 0 ? std::format("{:.4f}", avg_reward) : "N/A";
                const std::string ucb_str = std::isinf(current_score) ? "inf" : std::format("{:.4f}", current_score);
                const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->visit_count()));
                const auto ucb_colored = logging::colors::highlight_ucb(ucb_str);
                m_logger_->trace("  {} -> {} | visits={} | total={:7.4f} | avg={:6} | UCB={}",
                    child->name(), logging::colors::highlight_node(target->name()),
                    visits_str, target->total_reward(), avg_str, ucb_colored);
            } else {
                const std::string ucb_str = std::isinf(current_score) ? "inf" : std::format("{:.4f}", current_score);
                const auto ucb_colored = logging::colors::highlight_ucb(ucb_str);
                m_logger_->trace("  {} -> (null) | UCB={}", child->name(), ucb_colored);
            }
        }
    }

    for (const auto& child : m_child_action_)
    {
        const double current_score = child->upper_confidence_bound(2);
        if (best_child == nullptr || current_score > best_score)
        {
            best_score = current_score;
            best_child = child;
        }
    }
    if (m_logger_ && best_child && best_child->target())
    {
        const std::string ucb_str = std::isinf(best_score) ? "inf" : std::format("{:.4f}", best_score);
        const auto ucb_colored = logging::colors::highlight_ucb(ucb_str);
        m_logger_->debug("Selected: {} -> {} (UCB={})",
            best_child->name(), logging::colors::highlight_node(best_child->target()->name()), ucb_colored);
    }
    return best_child;
}

node_ptr Node::expand()
{
    const vector<action_ptr> child_actions = this->get_available_actions();
    if (child_actions.empty())
    {
        if (m_logger_) m_logger_->info("  Node '{}' has no available actions to expand.", name());
        return nullptr;
    }

    // Add all available actions as children
    if (m_logger_)
    {
        m_logger_->trace("Expanding '{}' (creating {} child node(s))", name(), child_actions.size());
    }

    for(const auto& child : child_actions)
    {
        child->generate();
        auto target = child->target();
        if (target) {
            m_child_action_.push_back(child);
            target->set_parent(child);
            if (m_logger_)
            {
                m_logger_->trace("  Created: {} → {}",
                    logging::colors::highlight_node(name()),
                    logging::colors::highlight_node(target->name()));
            }
        } else {
            if (m_logger_) m_logger_->error("  Node '{}' generated a null target for action '{}'", name(), child->name());
        }
    }

    // After adding all, we can return the first child's target node for simulation
    // This is typical for an immediate rollout after expansion.
    if (!m_child_action_.empty()) {
        if (m_logger_ && m_child_action_.front()->target())
        {
            m_logger_->debug("Expanded {} → first child: {}",
                logging::colors::highlight_node(name()),
                logging::colors::highlight_node(m_child_action_.front()->target()->name()));
        }
        return m_child_action_.front()->target();
    }

    return nullptr; // Should not happen if child_actions was not empty and generated targets
}


const_simulation_result_ptr Node::rollout()
{
    if (this->is_terminal_state())
    {
        const_simulation_result_ptr terminal_value = this->value();
        auto reward = interpret_result(terminal_value);
        if (m_logger_) m_logger_->trace("rollout: Terminal state reached at node '{}'. value: {:.4f}", name(), reward);
        return terminal_value;
    }

    auto select_strategy = rollout_strategy();
    if (!select_strategy)
    {
        if (m_logger_) m_logger_->error("No rollout strategy available for node '{}'", name());
        return nullptr; // Or throw, depending on error handling policy
    }

    vector<action_ptr> actions_for_rollout;
    // In rollout, we should typically consider all possible actions, not just sampled children
    actions_for_rollout = this->get_available_actions();

    if (actions_for_rollout.empty())
    {
        if (m_logger_) m_logger_->warn("rollout: Node '{}' has no available actions during simulation. Returning 0.0.", name());
        return nullptr; // If no moves, then game might be blocked or draw.
    }

    if (const auto selected_action = select_strategy->select_action(actions_for_rollout))
    {
        selected_action->generate(); // Ensure the target node exists
        if (auto new_node = selected_action->target())
        {
            if (m_logger_) m_logger_->trace("rollout: {} --({})--> {}", name(), selected_action->name(), new_node->name());
            const_simulation_result_ptr reward = new_node->rollout();
            return reward;
        }
        else
        {
            if (m_logger_) m_logger_->error("rollout: Action '{}' generated a null target node.", selected_action->name());
            return nullptr;
        }
    }
    else
    {
        if (m_logger_) m_logger_->warn("rollout: rollout strategy failed to select an action from node '{}'. Returning 0.0.", name());
        return nullptr;
    }
}

void Node::backpropagate(const const_simulation_result_ptr &result)
{
    // Capture before values for logging
    const unsigned long visit_count_before = m_visit_count_;
    const double total_reward_before = m_total_reward_;

    if (m_visit_count_ + 1 == 0) // Check for overflow before incrementing (unsigned long max + 1 = 0)
    {
        if (m_logger_) m_logger_->error("Visit count overflow detected for node '{}'", name());
        throw std::runtime_error("Node::backpropagate - visit count overflow");
    }

    // Check for double overflow/underflow
    const double reward = interpret_result(result);
    if ((reward > 0 && m_total_reward_ > std::numeric_limits<double>::max() - reward) ||
        (reward < 0 && m_total_reward_ < std::numeric_limits<double>::lowest() - reward))
    {
        if (m_logger_) m_logger_->error("Total reward overflow/underflow detected for node '{}'", name());
        throw std::runtime_error("Node::backpropagate - total reward overflow");
    }

    m_total_reward_ += reward;
    m_visit_count_++;

    if (m_logger_)
    {
        const auto visits_before_str = logging::colors::highlight_visits(std::format("{}", visit_count_before));
        const auto visits_after_str = logging::colors::highlight_visits(std::format("{}", m_visit_count_));
        const auto reward_before_str = logging::colors::highlight_reward(std::format("{:.4f}", total_reward_before));
        const auto reward_after_str = logging::colors::highlight_reward(std::format("{:.4f}", m_total_reward_));
        const auto reward_delta_str = logging::colors::highlight_reward(std::format("{:.4f}", reward));
        m_logger_->trace("  {}: visits {}→{} | reward {}→{} (Δ{})",
            logging::colors::highlight_node(name()),
            visits_before_str, visits_after_str,
            reward_before_str, reward_after_str, reward_delta_str);
    }

    if (const auto sp = m_parent_action_.lock())
    {
        if(const auto parent_node = sp->source())
        {
            parent_node->backpropagate(result);
        }
    }
}

std::string Node::name() const
{
    return m_name_;
}

double Node::upper_confidence_bound(const int c) const
{
    // If not visited, UCB is infinity to prioritize exploration
    if (m_visit_count_ == 0)
    {
        return std::numeric_limits<double>::infinity();
    }

    // Need parent's visit count for UCB calculation
    shared_ptr<Node> parent_node = nullptr;
    if (const auto sp = m_parent_action_.lock())
    {
        parent_node = sp->source();
    }

    // If no parent or parent visit count is 0, UCB formula is not applicable.
    // Return infinity to encourage exploration or handle as an error.
    if (!parent_node || parent_node->visit_count() == 0)
    {
        return std::numeric_limits<double>::infinity();
    }

    const double avg_reward = m_total_reward_ / m_visit_count_;
    const double value_term = avg_reward;
    const double exploration_term = c * std::sqrt(std::log(static_cast<double>(parent_node->visit_count())) / m_visit_count_);
    const double ucb_value = value_term + exploration_term;
    
    return ucb_value;
}

bool Node::is_leaf_node() const
{
    return m_child_action_.empty();
}

bool Node::has_been_sampled() const
{
    return m_visit_count_ > 0;
}

int Node::visit_count() const
{
    return m_visit_count_;
}

double Node::total_reward() const
{
    return m_total_reward_;
}

action_ptr Node::select_action()
{
    if (m_child_action_.empty())
    {
        if (m_logger_) m_logger_->warn("Node '{}' has no children. Cannot select action.", name());
        return nullptr;
    }

    // Select the child action with the highest average reward (exploitation)
    action_ptr best_child = nullptr;
    double max_avg_reward = -std::numeric_limits<double>::infinity();

    if (m_logger_) {
        std::stringstream ss;
        ss << "  Node '" << name() << "' - Final Action Selection (highest average reward):" << std::endl;
        for (const auto& child : m_child_action_) {
            if (auto target = child->target()) {
                double avg_reward = (target->visit_count() > 0) ? (target->total_reward() / target->visit_count()) : 0.0;
                ss << "    - Action leading to '" << target->name()
                   << std::format(" (Avg reward: {:.4f}, Visits: {})", avg_reward, target->visit_count()) << std::endl;
            } else {
                 ss << "    - Action leading to (nullptr)" << std::endl;
            }
        }
        m_logger_->debug("{}", ss.str());
    }

    for (const auto& child : m_child_action_)
    {
        auto target = child->target();
        if (target && target->visit_count() > 0)
        {
            double avg_reward = target->total_reward() / target->visit_count();
            if (avg_reward > max_avg_reward)
            {
                max_avg_reward = avg_reward;
                best_child = child;
            }
        }
    }

    // Fallback for nodes that were never visited (should be rare if iterations > 0)
    if (!best_child && !m_child_action_.empty()) {
        if (m_logger_) m_logger_->warn("  Node '{}' has no visited children. Falling back to most visited (which is 0).", name());
        int max_visits = -1;
        for (const auto& child : m_child_action_)
        {
            auto target = child->target();
            if (target && target->visit_count() > max_visits)
            {
                max_visits = target->visit_count();
                best_child = child;
            }
        }
    }

    if (m_logger_ && best_child && best_child->target()) {
        m_logger_->debug("  Node '{}' final selection: action leading to '{}' with avg reward of {:.4f}.", name(), best_child->target()->name(), max_avg_reward);
    }

    return best_child;
}






