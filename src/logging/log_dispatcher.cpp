#include <logging/log_dispatcher.h>

#include <logging/console_logger.h>
#include <logging/dummy_logger.h>
#include <logging/ilogger.h>

#include "logging/file_logger.h"
#include "logging/file_logger.h"


using sophia::logging::ConsoleLogger;
using sophia::logging::FileLogger;

namespace sophia::logging
{
    LogDispatcher::LogDispatcher(LogLevel min_level) : min_level_(min_level)
    {
        std::string directory = "/Users/lucsorenson/Repositories/Sophia-Core-Libraries/logs/";
        m_loggers_[LogChannel::UserInterface] = std::make_shared<ConsoleLogger>(min_level);
        m_loggers_[LogChannel::Decision] = std::make_shared<FileLogger>(directory + "decision.log", min_level);
        m_loggers_[LogChannel::Stats] = std::make_shared<FileLogger>(directory + "stats.log", min_level);
        m_loggers_[LogChannel::Trace] = std::make_shared<FileLogger>(directory + "trace.log", min_level);
        m_loggers_[LogChannel::Main] = std::make_shared<DummyLogger>(min_level);
    }

    void LogDispatcher::log(const LogLevel level, const LogChannel channel, const std::string& message)
    {
        const auto logger = m_loggers_[channel];
        if (logger == nullptr) throw std::runtime_error("Logger not found");

        logger->log(level, channel, message);
    }

} // namespace sophia::logging
