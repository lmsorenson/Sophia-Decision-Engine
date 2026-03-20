#ifndef SOPHIA_FILE_LOGGER_H
#define SOPHIA_FILE_LOGGER_H

#include <logging/ilogger.h>
#include <string>

namespace sophia::logging
{
    /**
     * @brief A concrete logger implementation that writes messages to the console (std::cout).
     */
    class FileLogger : public ILogger
    {
    public:
        /**
         * @brief Constructs a ConsoleLogger with a minimum log level.
         * @param min_level The minimum severity level to log. Messages below this level will be ignored.
         */
        explicit FileLogger(const std::string &filename, LogLevel min_level = LogLevel::Info);

    private:
        void log(LogLevel level, LogChannel channel, const std::string& message) override;

        LogLevel min_level_;
        std::string filename_;
    };

} // namespace sophia::logging

#endif //SOPHIA_FILE_LOGGER_H
