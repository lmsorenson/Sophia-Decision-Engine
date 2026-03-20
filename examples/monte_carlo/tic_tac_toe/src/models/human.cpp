#include <tic_tac_toe/models/human.h>
#include <monte_carlo/models/node.h>
#include <monte_carlo/models/action.h>
#include <tic_tac_toe/models/board.h>
#include <logging/ilogger.h> // Added include for ILogger

using sophia::monte_carlo::tic_tac_toe::models::Human;
using sophia::monte_carlo::tic_tac_toe::models::Board;
using sophia::monte_carlo::tic_tac_toe::models::Position;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::tic_tac_toe::const_position_ptr;
using sophia::monte_carlo::models::Action;
using sophia::monte_carlo::models::Node;
using std::shared_ptr;
using std::pair;

Human::Human(const Symbol symbol, std::function<std::string()> get_move_input_callback, const logger_ptr& logger)
    : Player(symbol, logger) // Pass logger to base Player constructor
    , get_move_input_callback_(std::move(get_move_input_callback))
    , m_logger_(logger)
{
    if (m_logger_) m_logger_->info("Human player created with symbol {}", enums::TileStateToString(symbol));
}

const_position_ptr Human::NextMove() const
{
    const_position_ptr position = nullptr;
    std::string move_str;

    while (position == nullptr)
    {
        if (m_logger_) m_logger_->display("Player {} (Human): Enter your move (e.g., A1) : ", enums::TileStateToString(m_player_symbol_));
        move_str = get_move_input_callback_(); // Get input from callback

        if (Position::IsValid(move_str))
        {
            auto coordinates = Position::ParseMove(move_str);
            position = std::make_shared<Position>(coordinates, m_player_symbol_);
        }
        else
        {
            if (m_logger_) m_logger_->warn("Invalid input format '{}'! Expected letter + digit (e.g., A1).", move_str);
        }
    }
    return position;
}

void Human::Update(const std::string message)
{
    if (m_logger_) m_logger_->info("Human received message: {}", message);
}


