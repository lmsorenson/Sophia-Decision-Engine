#include <logging/dummy_logger.h>

namespace sophia::logging
{
    DummyLogger::DummyLogger(const LogLevel min_level)
        : min_level_(min_level)
    {
    }

    void DummyLogger::log(const LogLevel level, LogChannel channel, const std::string& message)
    {
    }

} // namespace sophia::logging
