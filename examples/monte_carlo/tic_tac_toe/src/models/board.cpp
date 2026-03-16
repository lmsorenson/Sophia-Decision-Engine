#include <tic_tac_toe/models/board.h>
#include <tic_tac_toe/models/position.h>
#include <unordered_set>
#include <vector>
#include <logging/ilogger.h> // Added for logger_ptr
#include <sstream> // For building print string
#include <bit> // For popcount and countr_zero

using sophia::monte_carlo::tic_tac_toe::models::Board;
using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::tic_tac_toe::models::Player;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::tic_tac_toe::enums::Alignment;
using sophia::monte_carlo::tic_tac_toe::const_position_ptr;
using sophia::monte_carlo::tic_tac_toe::const_board_ptr;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::pair;

Board::Board(const logger_ptr& logger)
: m_logger_(logger)
{
    for(int row = 0; row < 3; row++)
    {
        vector<const_position_ptr> row_positions;

        for (int col = 0; col < 3; col++)
        {
            auto new_position = make_shared<Position>(std::pair(row, col), Symbol::None);
            row_positions.push_back(new_position);
        }

        m_tiles_.push_back(row_positions);
    }
    if (m_logger_) m_logger_->debug("Board created.");
}

Board::Board(const Board &other)
: m_tiles_(other.m_tiles_)
, last_placed_(other.last_placed_)
, m_logger_(other.m_logger_) // Copy logger
{
}

Board::Board(Board &&other) noexcept
: m_tiles_(std::move(other.m_tiles_))
, last_placed_(other.last_placed_)
, m_logger_(std::move(other.m_logger_)) // Move logger
{
}

Board & Board::operator=(const Board &other)
{
    if (this == &other)
        return *this;
    m_tiles_ = other.m_tiles_;
    last_placed_ = other.last_placed_;
    m_logger_ = other.m_logger_; // Assign logger
    return *this;
}

Board & Board::operator=(Board &&other) noexcept
{
    if (this == &other)
        return *this;
    m_tiles_ = std::move(other.m_tiles_);
    last_placed_ = other.last_placed_;
    m_logger_ = std::move(other.m_logger_); // Move assign logger
    return *this;
}


void Board::SetPosition(const Position &new_position)
{
    if (new_position.State() == Symbol::None)
    {
        throw std::invalid_argument("Can't set a position to empty.");
    }

    const auto [row, column] = new_position.Coordinates();

    const auto existing_position = m_tiles_[row][column];

    if (existing_position->State() != Symbol::None)
    {
        throw std::invalid_argument("Position already taken.");
    }

    auto placed_state = new_position.State();
    m_tiles_[row][column] = make_shared<Position>(std::pair( row, column ), placed_state);
    last_placed_ = placed_state;
}

Symbol Board::LastPlaced() const
{
    return last_placed_;
}

vector<const_position_ptr> Board::GetOpenPositions() const
{
    std::vector<const_position_ptr> open_positions = {};

    for(const auto& row : m_tiles_)
    {
        for (const auto& position : row)
        {
            if (position->State() == Symbol::None)
            {
                open_positions.push_back(position);
            }
        }
    }

    return open_positions;
}

int Board::GetMarkCount() const
{
    int count = 0;
    for (const auto& row : m_tiles_)
    {
        for (const auto& position : row)
        {
            if (position->State() != Symbol::None)
            {
                count++;
            }
        }
    }
    return count;
}

Board::BoardMask Board::ToMask() const
{
    BoardMask mask;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            const auto state = m_tiles_[row][col]->State();
            if (state == Symbol::None) continue;

            // bit index: row 0 (0,1,2), row 1 (3,4,5), row 2 (6,7,8)
            const int bit_index = row * 3 + col;
            const uint16_t bit = 1 << bit_index;

            if (state == Symbol::X)
            {
                mask.x_mask |= bit;
            }
            else if (state == Symbol::O)
            {
                mask.o_mask |= bit;
            }
        }
    }
    return mask;
}

std::vector<const_position_ptr> Board::GetWinningMoves(const enums::Symbol symbol) const
{
    if (symbol == enums::Symbol::None) return {};

    const auto [x_mask, o_mask] = ToMask();
    const uint16_t my_mask = (symbol == enums::Symbol::X) ? x_mask : o_mask;
    const uint16_t opp_mask = (symbol == enums::Symbol::X) ? o_mask : x_mask;

    // Define the 8 winning lines as bitmasks
    static constexpr uint16_t WIN_LINES[] = {
        0b000000111, // Row 0 (A1, A2, A3)
        0b000111000, // Row 1 (B1, B2, B3)
        0b111000000, // Row 2 (C1, C2, C3)
        0b001001001, // Col 0 (A1, B1, C1)
        0b010010010, // Col 1 (A2, B2, C2)
        0b100100100, // Col 2 (A3, B3, C3)
        0b100010001, // Diagonal (A1, B2, C3)
        0b001010100  // Anti-diagonal (A3, B2, C1)
    };

    std::vector<const_position_ptr> winning_moves;
    std::unordered_set<int> added_indices;

    for (const uint16_t line : WIN_LINES)
    {
        // Check if I have 2 pieces in this line and opponent has 0
        if (std::popcount(static_cast<unsigned int>(my_mask & line)) == 2 && 
            (opp_mask & line) == 0)
        {
            // The winning move is the one empty bit in this line
            const uint16_t winning_bit = line ^ (my_mask & line);
            const int bit_index = std::countr_zero(winning_bit);
            
            if (added_indices.find(bit_index) == added_indices.end())
            {
                const int row = bit_index / 3;
                const int col = bit_index % 3;
                winning_moves.push_back(m_tiles_[row][col]);
                added_indices.insert(bit_index);
            }
        }
    }

    return winning_moves;
}


const_board_ptr Board::WithMove(const Position &position) const
{
    try
    {
        Board newBoard = *this; // Create a copy, which also copies the logger

        newBoard.SetPosition(position);

        return make_shared<Board>(newBoard);
    }
    catch (const std::invalid_argument &e)
    {
        if (m_logger_) m_logger_->error("Invalid move exception in WithMove: {}", e.what());
        return nullptr;
    }
}

shared_ptr<std::pair<Symbol, bool>> Board::Winner() const
{
    const auto list = {
        GetLines(Alignment::Horizontal),
        GetLines(Alignment::Vertical),
        GetLines(Alignment::Diagonal)
    };

    for(const auto& line_type : list)
    {
        for(auto line : line_type)
        {
            std::unordered_set unique_set(line.begin(), line.end());
            std::vector unique_vec(unique_set.begin(), unique_set.end());
            if (unique_vec.size() == 1 && unique_vec.front() != Symbol::None)
            {
                return std::make_shared<std::pair<Symbol, bool>>(unique_vec.front(), true);
            }
        }
    }
    return nullptr;
}

void Board::Print() const
{
    if (!m_logger_) return; // Don't print if no logger

    std::stringstream ss;
    ss << "    1   2   3 " << std::endl;
    auto column_letter = { "A", "B", "C" };
    auto itr = column_letter.begin();
    bool first_row = true;

    for (const auto& row : m_tiles_)
    {
        if (!first_row)
        {
            ss << "   ---+---+---" << std::endl;
        }
        first_row = false;

        ss << " " << *itr << " ";
        itr++;

        bool first_col = true;
        for (const auto& position : row)
        {
            if (!first_col)
            {
                ss << "|";
            }
            first_col = false;
            ss << " " << enums::TileStateToString(position->State()) << " ";
        }
        ss << std::endl;
    }
    m_logger_->info("Board state:\n{}", ss.str());
}


std::vector<std::vector<Symbol>> Board::GetLines(const Alignment alignment) const
{
    switch (alignment)
    {
        case Alignment::Horizontal:
            return {
                {
                    m_tiles_[0][0]->State(),
                    m_tiles_[0][1]->State(),
                    m_tiles_[0][2]->State()
                },
                {
                    m_tiles_[1][0]->State(),
                    m_tiles_[1][1]->State(),
                    m_tiles_[1][2]->State()
                },
                {
                    m_tiles_[2][0]->State(),
                    m_tiles_[2][1]->State(),
                    m_tiles_[2][2]->State()
                }
            };
        case Alignment::Vertical:
            return {
                    {
                        m_tiles_[0][0]->State(),
                        m_tiles_[1][0]->State(),
                        m_tiles_[2][0]->State()
                    },
                    {
                        m_tiles_[0][1]->State(),
                        m_tiles_[1][1]->State(),
                        m_tiles_[2][1]->State()
                    },
                    {
                        m_tiles_[0][2]->State(),
                        m_tiles_[1][2]->State(),
                        m_tiles_[2][2]->State()
                    },
                };
        case Alignment::Diagonal:
            return {
                    {
                        m_tiles_[0][0]->State(),
                        m_tiles_[1][1]->State(),
                        m_tiles_[2][2]->State()
                    },
                    {
                        m_tiles_[2][0]->State(),
                        m_tiles_[1][1]->State(),
                        m_tiles_[0][2]->State()
                    }
                };
        default: return {};
    }
}
