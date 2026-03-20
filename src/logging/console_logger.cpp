#include <logging/console_logger.h>
#include <iostream>
#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define STDOUT_FILENO 1
#else
#include <unistd.h>
#endif

namespace sophia::logging
{
    // ANSI color codes
    namespace colors
    {
        constexpr const char* RESET = "\033[0m";
        constexpr const char* BOLD = "\033[1m";
        
        // Log level colors
        constexpr const char* TRACE = "\033[90m";      // Dark gray
        constexpr const char* DEBUG = "\033[36m";       // Cyan
        constexpr const char* INFO = "\033[34m";        // Blue
        constexpr const char* WARN = "\033[33m";         // Yellow
        constexpr const char* ERROR = "\033[31m";        // Red
        
        // Phase colors
        constexpr const char* PHASE_SELECTION = "\033[94m";      // Light blue
        constexpr const char* PHASE_EXPANSION = "\033[92m";      // Light green
        constexpr const char* PHASE_ROLLOUT = "\033[95m";        // Light magenta
        constexpr const char* PHASE_BACKPROP = "\033[93m";      // Light yellow
        
        // Highlight colors
        constexpr const char* HIGHLIGHT_VALUE = "\033[96m";      // Bright cyan
        constexpr const char* HIGHLIGHT_UCB = "\033[91m";        // Bright red
        constexpr const char* HIGHLIGHT_REWARD = "\033[92m";     // Green
        constexpr const char* HIGHLIGHT_VISITS = "\033[93m";     // Yellow
    }
    
    static bool is_terminal()
    {
        return isatty(STDOUT_FILENO) != 0;
    }

    ConsoleLogger::ConsoleLogger(LogLevel min_level) : min_level_(min_level) {}

    void ConsoleLogger::log(const LogLevel level, LogChannel channel, const std::string& message)
    {
        if (level < min_level_)
        {
            return;
        }

        const bool use_colors = is_terminal();
        const char* level_str;
        const char* color = "";
        const char* reset = use_colors ? colors::RESET : "";
        
        switch (level)
        {
            case LogLevel::None:
                level_str = "";
                break;
            case LogLevel::Trace:
                level_str = "[TRACE]";
                color = use_colors ? colors::TRACE : "";
                break;
            case LogLevel::Debug:
                level_str = "[DEBUG]";
                color = use_colors ? colors::DEBUG : "";
                break;
            case LogLevel::Info:
                level_str = "[INFO] ";
                color = use_colors ? colors::INFO : "";
                break;
            case LogLevel::Warn:
                level_str = "[WARN] ";
                color = use_colors ? colors::WARN : "";
                break;
            case LogLevel::Error:
                level_str = "[ERROR]";
                color = use_colors ? colors::ERROR : "";
                break;
            default:
                level_str = "[UNKN] ";
                color = "";
                break;
        }

        // For errors, log to std::cerr. For all others, log to std::cout.
        if (level == LogLevel::Error)
        {
            std::cerr << color << level_str << reset << " " << message << std::endl;
        }
        else
        {
            std::cout << color << level_str << reset << " " << message << std::endl;
        }
    }

} // namespace sophia::logging
