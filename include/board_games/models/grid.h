#ifndef SOPHIA_BOARD_GAMES_GRID_H
#define SOPHIA_BOARD_GAMES_GRID_H

#include <vector>
#include <optional>
#include <stdexcept>
#include <board_games/models/coordinate.h>

namespace sophia::board_games::models
{
    /**
     * @class Grid
     * @brief A generic 2D container for board games.
     */
    template<typename T>
    class Grid
    {
    public:
        Grid(int rows, int cols)
            : m_rows(rows), m_cols(cols), m_cells(rows, std::vector<T>(cols))
        {}

        Grid(int rows, int cols, const T& initial_value)
            : m_rows(rows), m_cols(cols), m_cells(rows, std::vector<T>(cols, initial_value))
        {}

        [[nodiscard]] int rows() const { return m_rows; }
        [[nodiscard]] int cols() const { return m_cols; }

        [[nodiscard]] T& at(const Coordinate& coord)
        {
            validate(coord);
            return m_cells[coord.row][coord.col];
        }

        [[nodiscard]] const T& at(const Coordinate& coord) const
        {
            validate(coord);
            return m_cells[coord.row][coord.col];
        }

        [[nodiscard]] bool is_valid(const Coordinate& coord) const
        {
            return coord.row >= 0 && coord.row < m_rows &&
                   coord.col >= 0 && coord.col < m_cols;
        }

    private:
        void validate(const Coordinate& coord) const
        {
            if (!is_valid(coord))
            {
                throw std::out_of_range("Coordinate out of grid bounds");
            }
        }

        int m_rows;
        int m_cols;
        std::vector<std::vector<T>> m_cells;
    };
}

#endif //SOPHIA_BOARD_GAMES_GRID_H
