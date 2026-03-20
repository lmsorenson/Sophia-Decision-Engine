#include <logging/log_dispatcher.h>

#include <logging/console_logger.h>
#include <logging/logger2.h>
#include <logging/ilogger.h>


using sophia::logging::ConsoleLogger;

namespace sophia::logging
{
    LogDispatcher::LogDispatcher(LogLevel min_level) : min_level_(min_level)
    {
        m_loggers_[LogChannel::UserInterface] = std::make_shared<ConsoleLogger>(min_level);
        m_loggers_[LogChannel::Main] = std::make_shared<Logger2>(min_level);
    }

    void LogDispatcher::log(const LogLevel level, const LogChannel channel, const std::string& message)
    {
        const auto logger = m_loggers_[channel];
        if (logger == nullptr) throw std::runtime_error("Logger not found");

        logger->log(level, channel, message);
    }

} // namespace sophia::logging
