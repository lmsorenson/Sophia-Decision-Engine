#ifndef POSITION_H
#define POSITION_H

#include <utility>
#include <tic_tac_toe/enums/symbol.h>

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @class Position
     * @brief Refers to a move that a Player can make in a Tic Tac Toe Game.
     * A position can be empty, it can have an X Symbol, or it can have an O Symbol.
     */
    class Position
    {
    public:
        /**
         * @brief Creates an instance of a Position.
         * @param coordinates The coordinates of the position.
         * The first element represents a row, the second represents a column.
         */
        explicit Position(const std::pair<int, int> &coordinates);

        /**
         * @brief Creates an instance of a Position.
         * @param coordinates The coordinates of the position.
         * The first element represents a row, the second represents a column.
         * @param symbol The symbol being applied to the Position.
         */
        Position(const std::pair<int, int> &coordinates, enums::Symbol symbol);

        /**
         * Gets the name of the Position.
         * @return A string with the name of the Position.
         */
        [[nodiscard]] std::string name() const;

        /**
         * Gets the coordinates of the position where:
        * The first element represents a row, the second represents a column.
         * @return The coordinates of the position.
         */
        [[nodiscard]] std::pair<int, int> Coordinates() const;

        /**
         * Gets the Symbol written on the Position.
         * @return The Symbol that is written on the Position.
         */
        [[nodiscard]] enums::Symbol State() const;

        /**
         * @brief Gets a copy of the Position with the given Symbol applied.
         * @param new_state The new state of the Position.
         * @return The Position with the given Symbol applied.
         */
        [[nodiscard]] Position WithState(enums::Symbol new_state) const;


        /**
         * @brief Parses a move from a Move name.
         * @param input A 2-letter move name.
         * @return A pair of coordinates where:
         * The first element represents a row, the second represents a column.
         */
        static std::pair<int,int> ParseMove(const std::string &input);

        /**
         * @brief Determines if the given move name can be successfully parsed.
         * @param input A 2-letter move name.
         * @return A boolean indicating if the given move name is a valid move name.
         */
        static bool IsValid(const std::string &input);

    private:
        int m_row_index_ = 0;
        int m_column_index_ = 0;
        enums::Symbol m_state_ = enums::Symbol::None;
    };
}

#endif //POSITION_H