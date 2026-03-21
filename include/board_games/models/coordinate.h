#ifndef SOPHIA_BOARD_GAMES_COORDINATE_H
#define SOPHIA_BOARD_GAMES_COORDINATE_H

#include <string>
#include <utility>

namespace sophia::board_games::models
{
    /**
     * @struct Coordinate
     * @brief A simple value type representing a position on a 2D grid.
     */
    struct Coordinate
    {
        int row;
        int col;

        Coordinate(int r, int c) : row(r), col(c) {}

        /**
         * @brief Returns the name of the coordinate in "A1" format.
         */
        [[nodiscard]] std::string name() const;

        /**
         * @brief Parses a coordinate from a string like "A1".
         */
        static Coordinate parse(const std::string& input);

        bool operator==(const Coordinate& other) const = default;
    };
}

#endif //SOPHIA_BOARD_GAMES_COORDINATE_H
