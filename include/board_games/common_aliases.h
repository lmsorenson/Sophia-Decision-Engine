#ifndef SOPHIA_BOARD_GAMES_COMMON_ALIASES_H
#define SOPHIA_BOARD_GAMES_COMMON_ALIASES_H

#include <memory>
#include <logging/ilogger.h>

namespace sophia::board_games
{
    using logger_ptr = std::shared_ptr<logging::ILogger>;
    using const_logger_ptr = std::shared_ptr<const logging::ILogger>;
}

#endif //SOPHIA_BOARD_GAMES_COMMON_ALIASES_H
