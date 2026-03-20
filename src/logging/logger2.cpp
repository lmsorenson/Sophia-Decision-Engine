#include <logging/logger2.h>

namespace sophia::logging
{
    Logger2::Logger2(const LogLevel min_level)
        : min_level_(min_level)
    {
    }

    void Logger2::log(const LogLevel level, LogChannel channel, const std::string& message)
    {
    }

} // namespace sophia::logging
