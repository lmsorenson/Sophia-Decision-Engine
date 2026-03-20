#include <tic_tac_toe/models/tic_tac_toe_simulation_result.h>

using sophia::monte_carlo::tic_tac_toe::models::TicTacToeSimulationResult;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;

TicTacToeSimulationResult::TicTacToeSimulationResult(Symbol winner)
    : m_winner_(winner)
{
}

Symbol TicTacToeSimulationResult::Winner() const
{
    return m_winner_;
}

double TicTacToeSimulationResult::reward() const
{
    return 0.0;
}
