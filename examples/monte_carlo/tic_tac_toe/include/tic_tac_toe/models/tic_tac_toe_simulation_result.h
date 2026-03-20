#ifndef TIC_TAC_TOE_SIMULATION_RESULT_H
#define TIC_TAC_TOE_SIMULATION_RESULT_H

#include <monte_carlo/models/simulation_result.h>
#include <tic_tac_toe/enums/symbol.h>

namespace sophia::monte_carlo::tic_tac_toe::models
{
    /**
     * @brief Specialized simulation result for Tic Tac Toe.
     *
     * Stores the winner of the simulation.
     */
    class TicTacToeSimulationResult : public sophia::monte_carlo::models::SimulationResult
    {
    public:
        explicit TicTacToeSimulationResult(enums::Symbol winner);
        ~TicTacToeSimulationResult() override = default;

        /**
         * @brief Gets the symbol of the winner.
         * @return The winner's symbol (X, O, or None for a draw).
         */
        [[nodiscard]] enums::Symbol Winner() const;

        [[nodiscard]] double reward() const override;

    private:
        enums::Symbol m_winner_;
    };
}

#endif //TIC_TAC_TOE_SIMULATION_RESULT_H
