#ifndef SOPHIA_CONSOLE_LOGGER_H
#define SOPHIA_CONSOLE_LOGGER_H

#include <logging/ilogger.h>

namespace sophia::logging
{
    /**
     * @brief A concrete logger implementation that writes messages to the console (std::cout).
     */
    class ConsoleLogger : public ILogger
    {
    public:
        /**
         * @brief Constructs a ConsoleLogger with a minimum log level.
         * @param min_level The minimum severity level to log. Messages below this level will be ignored.
         */
        explicit ConsoleLogger(LogLevel min_level = LogLevel::Info);

    private:
        void log(LogLevel level, LogChannel channel, const std::string& message) override;

        LogLevel min_level_;
    };

} // namespace sophia::logging

#endif //SOPHIA_CONSOLE_LOGGER_H
