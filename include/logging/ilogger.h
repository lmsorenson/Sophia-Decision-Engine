#ifndef SOPHIA_LOGGING_ILOGGER_H
#define SOPHIA_LOGGING_ILOGGER_H

#include <string>
#include <format>

namespace sophia::logging
{
    /**
     * @brief Defines the severity levels for log messages.
     */
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    /**
     * @brief An interface for a generic, type-safe, and performant logger.
     *
     * This interface uses std::format for type-safe message formatting and defers
     * the formatting until after the log level has been checked, providing
     * performance benefits.
     *
     * Concrete implementations (e.g., ConsoleLogger, FileLogger) must implement
     * the private virtual `log` method.
     */
    class ILogger
    {
    public:
        virtual ~ILogger() = default;

        /**
         * @brief Logs a message with TRACE severity (most verbose).
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void trace(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::TRACE, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with DEBUG severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void debug(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::DEBUG, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with INFO severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void info(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::INFO, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with WARN severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void warn(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::WARN, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with ERROR severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void error(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::ERROR, std::format(fmt, std::forward<Args>(args)...));
        }

    private:
        /**
         * @brief The core logging function that concrete loggers must implement.
         * @param level The severity level of the message.
         * @param message The fully formatted message to be logged.
         */
        virtual void log(LogLevel level, const std::string& message) = 0;
    };

} // namespace sophia::logging

#endif // SOPHIA_LOGGING_ILOGGER_H
