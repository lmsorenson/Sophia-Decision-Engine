#ifndef SOPHIA_LOGGING_COLORS_H
#define SOPHIA_LOGGING_COLORS_H

#include <string>
#include <format>

namespace sophia::logging::colors
{
    // ANSI color codes
    inline constexpr const char* RESET = "\033[0m";
    inline constexpr const char* BOLD = "\033[1m";
    
    // Phase colors
    inline constexpr const char* PHASE_SELECTION = "\033[94m";      // Light blue
    inline constexpr const char* PHASE_EXPANSION = "\033[92m";      // Light green
    inline constexpr const char* PHASE_ROLLOUT = "\033[95m";         // Light magenta
    inline constexpr const char* PHASE_BACKPROP = "\033[93m";       // Light yellow
    
    // Highlight colors
    inline constexpr const char* HIGHLIGHT_VALUE = "\033[96m";       // Bright cyan
    inline constexpr const char* HIGHLIGHT_UCB = "\033[91m";        // Bright red
    inline constexpr const char* HIGHLIGHT_REWARD = "\033[92m";     // Green
    inline constexpr const char* HIGHLIGHT_VISITS = "\033[93m";     // Yellow
    inline constexpr const char* HIGHLIGHT_NODE = "\033[97m";      // White/bright
    
    // Helper functions to wrap text with colors
    inline std::string phase_selection(const std::string& text) { return std::string(PHASE_SELECTION) + text + RESET; }
    inline std::string phase_expansion(const std::string& text) { return std::string(PHASE_EXPANSION) + text + RESET; }
    inline std::string phase_rollout(const std::string& text) { return std::string(PHASE_ROLLOUT) + text + RESET; }
    inline std::string phase_backprop(const std::string& text) { return std::string(PHASE_BACKPROP) + text + RESET; }
    
    inline std::string highlight_ucb(const std::string& text) { return std::string(HIGHLIGHT_UCB) + BOLD + text + RESET; }
    inline std::string highlight_reward(const std::string& text) { return std::string(HIGHLIGHT_REWARD) + BOLD + text + RESET; }
    inline std::string highlight_visits(const std::string& text) { return std::string(HIGHLIGHT_VISITS) + BOLD + text + RESET; }
    inline std::string highlight_node(const std::string& text) { return std::string(HIGHLIGHT_NODE) + text + RESET; }
    
    // Format helpers that return colored strings
    template<typename... Args>
    inline std::string highlight_ucb_fmt(std::format_string<Args...> fmt, Args&&... args) {
        return highlight_ucb(std::format(fmt, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    inline std::string highlight_reward_fmt(std::format_string<Args...> fmt, Args&&... args) {
        return highlight_reward(std::format(fmt, std::forward<Args>(args)...));
    }
    
    template<typename... Args>
    inline std::string highlight_visits_fmt(std::format_string<Args...> fmt, Args&&... args) {
        return highlight_visits(std::format(fmt, std::forward<Args>(args)...));
    }
}

#endif // SOPHIA_LOGGING_COLORS_H
