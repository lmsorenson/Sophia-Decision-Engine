#ifndef SOPHIA_BOARD_GAMES_PLAYER_SIDE_H
#define SOPHIA_BOARD_GAMES_PLAYER_SIDE_H

#include <string>

namespace sophia::board_games::enums
{
    /**
     * @enum PlayerSide
     * @brief A generic representation of a player's side or team.
     */
    enum class PlayerSide
    {
        None = 0,
        First,
        Second,
        Third,
        Fourth
    };

    inline std::string to_string(PlayerSide side)
    {
        switch (side)
        {
            case PlayerSide::First: return "First";
            case PlayerSide::Second: return "Second";
            case PlayerSide::Third: return "Third";
            case PlayerSide::Fourth: return "Fourth";
            default: return "None";
        }
    }
}

#endif //SOPHIA_BOARD_GAMES_PLAYER_SIDE_H
