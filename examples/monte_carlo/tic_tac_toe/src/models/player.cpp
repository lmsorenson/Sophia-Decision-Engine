#include <tic_tac_toe/models/player.h>
#include <tic_tac_toe/models/board.h>
#include <logging/ilogger.h> // Added include for ILogger

using sophia::monte_carlo::tic_tac_toe::models::Player;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::tic_tac_toe::models::Board;

Player::Player(const Symbol symbol, const logger_ptr& logger)
: m_player_symbol_(symbol)
, m_logger_(logger)
{
}

Symbol Player::symbol() const
{
    return m_player_symbol_;
}

double Player::value(const Board &board) const
{
    if (const auto winner = board.Winner())
    {
        if (winner->first == m_player_symbol_)
        {
            if (m_logger_) m_logger_->info("Player {} wins :)", enums::TileStateToString(m_player_symbol_));
            return 2.0;
        }

        if (m_logger_) m_logger_->info("Player {} loses :(", enums::TileStateToString(m_player_symbol_));
        return 0.0;
    }

    if (m_logger_) m_logger_->info("It's a draw :/");
    return 1.0;
}
