#include <logging/file_logger.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace sophia::logging
{
    FileLogger::FileLogger(const std::filesystem::path &filename, LogLevel min_level)
        : filename_(filename)
        , min_level_(min_level)
    {
        if (std::ofstream file(filename.c_str()); file.is_open())
        {
            file.close();
        }
    }

    void FileLogger::log(const LogLevel level, LogChannel channel, const std::string& message)
    {
        if (std::ofstream file(filename_.c_str(), std::ios::app); file.is_open())
        {
            file << message << std::endl;
            file.close();
        }
    }

} // namespace sophia::logging
