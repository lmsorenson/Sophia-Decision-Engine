#include <tic_tac_toe/models/game_state.h>

#include <utility>

using sophia::monte_carlo::tic_tac_toe::models::GameState;
using sophia::monte_carlo::tic_tac_toe::models::Board;
using sophia::monte_carlo::tic_tac_toe::models::Player;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::tic_tac_toe::const_game_state_ptr;
using sophia::monte_carlo::tic_tac_toe::const_board_ptr;
using sophia::monte_carlo::tic_tac_toe::const_position_ptr;
using sophia::monte_carlo::tic_tac_toe::const_player_ptr;

GameState::GameState(const const_game_ptr& game, const_player_ptr you, const_board_ptr board)
    : m_game_(game)
    , m_you_(std::move(you))
    , m_board_(std::move(board))
{
}

GameState::GameState(const const_game_ptr &game, const_player_ptr you, const_board_ptr board, Symbol last_placed)
    : m_game_(game)
    , m_you_(std::move(you))
    , m_board_(std::move(board))
{
}

const_game_state_ptr GameState::ApplyMove(const Position &position) const
{
    auto new_board = m_board_->WithMove(position);

    return std::make_shared<GameState>(m_game_.lock(), m_you_, new_board, position.State());
}

const_player_ptr GameState::CurrentPlayer() const
{
    // If board has even number of marks, it's X's turn. If odd, it's O's turn.
    // This assumes X always starts.
    const auto count = m_board_->GetMarkCount();
    const Symbol current_symbol = (count % 2 == 0) ? Symbol::X : Symbol::O;
    
    // Note: We don't have easy access to the actual Player object for the opponent here
    // without more context. But for heuristics, we often just need the symbol.
    // For now, we return m_you_ if its symbol matches, otherwise we'd need a player registry.
    return m_you_; 
}

const_player_ptr GameState::You() const
{
    return m_you_;
}

std::shared_ptr<std::pair<Symbol, bool>> GameState::Winner() const
{
    return m_board_->Winner();
}

std::vector<const_position_ptr> GameState::GetOpenPositions() const
{
    return m_board_->GetOpenPositions();
}

std::vector<const_position_ptr> GameState::GetWinningMoves() const
{
    const auto count = m_board_->GetMarkCount();
    const Symbol current_symbol = (count % 2 == 0) ? Symbol::X : Symbol::O;
    return m_board_->GetWinningMoves(current_symbol);
}

std::vector<const_position_ptr> GameState::GetBlockingMoves() const
{
    const auto count = m_board_->GetMarkCount();
    const Symbol opponent_symbol = (count % 2 == 0) ? Symbol::O : Symbol::X;
    return m_board_->GetWinningMoves(opponent_symbol);
}

Symbol GameState::LastPlaced() const
{
    return m_board_->LastPlaced();
}

Board GameState::GetBoard() const
{
    return *m_board_;
}

int GameState::GetTurnNumber() const
{
    return m_board_->GetMarkCount();
}

void GameState::Print() const
{
    m_board_->Print();
}
