#ifndef SOPHIA_ILOGGER_H
#define SOPHIA_ILOGGER_H

#include <string>
#include <memory>
#include <format>

namespace sophia::logging
{
    /**
     * @brief Defines the severity levels for log messages.
     */
    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        None
    };

    /**
     * @brief Defines the output channel for log messages.
     */
    enum class LogChannel
    {
        Main,
        UserInterface
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
        friend class LogDispatcher;

    public:
        virtual ~ILogger() = default;

        /**
         * @brief Logs a message with TRACE severity (most verbose).
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void display(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::None, LogChannel::UserInterface, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with TRACE severity (most verbose).
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void trace(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Trace, LogChannel::Main, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with DEBUG severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void debug(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Debug, LogChannel::Main, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with INFO severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void info(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Info, LogChannel::Main, std::format(fmt, std::forward<Args>(args)...));
        }

        template<typename... Args>
        void info(LogChannel channel, std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Info, channel, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with WARN severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void warn(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Warn, LogChannel::Main, std::format(fmt, std::forward<Args>(args)...));
        }

        /**
         * @brief Logs a message with ERROR severity.
         * @param fmt A std::format-compatible format string.
         * @param args The arguments to be formatted.
         */
        template<typename... Args>
        void error(std::format_string<Args...> fmt, Args&&... args)
        {
            log(LogLevel::Warn, LogChannel::Main, std::format(fmt, std::forward<Args>(args)...));
        }

    private:
        /**
         * @brief The core logging function that concrete loggers must implement.
         * @param level The severity level of the message.
         * @param message The fully formatted message to be logged.
         * @param channel The output channel for the message.
         */
        virtual void log(LogLevel level, LogChannel channel, const std::string& message) = 0;
    };

} // namespace sophia::logging

#endif //SOPHIA_ILOGGER_H
