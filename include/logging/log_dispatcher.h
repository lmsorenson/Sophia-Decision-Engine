#ifndef SOPHIA_LOG_DISPATCHER_H
#define SOPHIA_LOG_DISPATCHER_H

#include <logging/ilogger.h>
#include <map>

#include "monte_carlo/common_aliases.h"

namespace sophia::logging
{
    /**
     * @brief A concrete logger implementation that writes messages to the console (std::cout).
     */
    class LogDispatcher : public ILogger
    {
    public:
        /**
         * @brief Constructs a ConsoleLogger with a minimum log level.
         * @param log_directory The directory to store log files.
         * @param min_level The minimum severity level to log. Messages below this level will be ignored.
         */
        explicit LogDispatcher(const std::string &log_directory, LogLevel min_level = LogLevel::Info);

    private:
        void log(LogLevel level, LogChannel channel, const std::string& message) override;

        LogLevel min_level_;
        std::map<LogChannel, monte_carlo::logger_ptr> m_loggers_;
    };

} // namespace sophia::logging

#endif //SOPHIA_LOG_DISPATCHER_H
