#include <tic_tac_toe/models/position.h>
#include <tic_tac_toe/models/state.h>
#include <vector>
#include <utility>

using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using std::shared_ptr;
using std::vector;

Position::Position(const std::pair<int, int> &coordinates)
{
    m_row_index_ = coordinates.first;
    m_column_index_ = coordinates.second;
    m_state_ = enums::Symbol::None;
}

Position::Position(const std::pair<int, int> &coordinates, const Symbol tile_state)
{
    m_row_index_ = coordinates.first;
    m_column_index_ = coordinates.second;
    m_state_ = tile_state;
}

std::string Position::name() const
{
    const char row = static_cast<char>('A' + m_row_index_);
    const char letter = static_cast<char>('0' + m_column_index_ + 1);
    std::string str(1, row);
    str += letter;
    return str;
}

std::pair<int, int> Position::Coordinates() const
{
    return { m_row_index_, m_column_index_ };
}

Symbol Position::State() const
{
    return m_state_;
}

Position Position::WithState(const Symbol new_state) const
{
    auto new_position = *this;

    new_position.m_state_ = new_state;

    return new_position;
}

std::pair<int, int> Position::ParseMove(const std::string &input)
{
    if (input.length() != 2)
    {
        throw std::invalid_argument("Invalid input format!");
    }

    int r = std::toupper(input[0]) - 'A' + 1;
    int c = input[1] - '0';

    return { r - 1, c - 1 };
}

bool Position::IsValid(const std::string &input)
{
    bool is_valid = input.length() == 2;
    is_valid = is_valid && std::isalpha(input[0]);
    is_valid = is_valid && std::isdigit(input[1]);
    if (!is_valid)
    {
        return is_valid;
    }

    const char row_letter = input[0];
    int r = std::toupper(row_letter) - 'A' + 1;
    is_valid = r >= 1 && r <= 3;
    if (!is_valid)
    {
        return is_valid;
    }

    int c = input[1] - '0';
    is_valid = c >= 1 && c <= 3;
    if (!is_valid)
    {
        return is_valid;
    }

    return true;
}


