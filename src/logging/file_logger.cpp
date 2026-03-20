#include <logging/file_logger.h>
#include <fstream>

namespace sophia::logging
{
    FileLogger::FileLogger(const std::string &filename, LogLevel min_level)
        : filename_(filename)
        , min_level_(min_level)
    {
    }

    void FileLogger::log(const LogLevel level, LogChannel channel, const std::string& message)
    {
        std::ofstream outFile(filename_, std::ios::app);

        if (outFile.is_open()) {
            outFile << message << std::endl;

            outFile.close();
        }
    }

} // namespace sophia::logging
