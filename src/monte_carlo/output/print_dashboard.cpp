#include <monte_carlo/output/print_dashboard.h>
#include <monte_carlo/models/node.h>
#include <monte_carlo/models/action.h>
#include <logging/ilogger.h>
#include <logging/colors.h>

using sophia::monte_carlo::output::Dashboard;
using sophia::monte_carlo::models::Node;
using std::shared_ptr;

void Dashboard::print(const node_ptr &node, const logger_ptr& logger)
{
    const auto best_action = node->select_action();
    
    if (logger)
    {
        logger->display(logging::LogChannel::Stats, "\033[2J\033[3J\033[H");
        logger->display(logging::LogChannel::Stats, "\n--- MCTS Complete: Final Action Summary ---");
        logger->display(logging::LogChannel::Stats, "{:<25} | {:<12} | {:<15} | {:<12} | {:<12} | {:<10}",
            "Action (-> Node)", "Visits", "Total reward", "Avg reward", "UCB (c=2)", "Selected");
        logger->display(logging::LogChannel::Stats, "--------------------------------------------------------------------------------------------------------");

        auto final_actions = node->children();
        
        for (const auto& action : final_actions)
        {
            auto target = action->target();
            if (target && target->visit_count() > 0)
            {
                double avg_reward = target->total_reward() / target->visit_count();
                double ucb_value = target->upper_confidence_bound(2);
                std::string action_name = "'" + action->name() + "' -> '" + target->name() + "'";
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                
                const auto visits_str = logging::colors::highlight_visits(std::format("{:<12}", target->visit_count()));
                const auto reward_str = logging::colors::highlight_reward(std::format("{:<15.4f}", target->total_reward()));
                const auto avg_str = logging::colors::highlight_reward(std::format("{:<12.4f}", avg_reward));
                
                if (std::isinf(ucb_value))
                {
                    const auto ucb_str = logging::colors::highlight_ucb(std::format("{:<12}", "inf"));
                    logger->display(logging::LogChannel::Stats, "{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}",
                        action_name, visits_str, reward_str, avg_str, ucb_str, selected_str);
                }
                else
                {
                    const auto ucb_str = logging::colors::highlight_ucb(std::format("{:<12.4f}", ucb_value));
                    logger->display(logging::LogChannel::Stats, "{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}",
                        action_name, visits_str, reward_str, avg_str, ucb_str, selected_str);
                }
            }
            else
            {
                std::string action_name = action->name();
                bool is_selected = (best_action && best_action == action);
                std::string selected_str = is_selected ? "✓" : "";
                logger->display(logging::LogChannel::Stats, "{:<25} | {:<12} | {:<15} | {:<15} | {:<12} | {:<10}",
                    action_name, "0", "N/A", "N/A", "N/A", selected_str);
            }
        }
        logger->display(logging::LogChannel::Stats, "--------------------------------------------------------------------------------------------------------");
    }
    if (logger && best_action && best_action->target())
    {
        auto target = best_action->target();
        double avg_reward = target->visit_count() > 0 ? target->total_reward() / target->visit_count() : 0.0;
        const auto visits_str = logging::colors::highlight_visits(std::format("{}", target->visit_count()));
        const auto total_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", target->total_reward()));
        const auto avg_reward_str = logging::colors::highlight_reward(std::format("{:.4f}", avg_reward));
        logger->display(logging::LogChannel::Stats, "=> Best Action Selected: '{}' -> {} (visits={}, total_reward={}, avg_reward={})",
            best_action->name(), logging::colors::highlight_node(target->name()),
            visits_str, total_reward_str, avg_reward_str);
    } else if (logger)
    {
        logger->warn("=> No best action could be selected.");
    }
}

