#ifndef SOPHIA_MONTE_CARLO_MODELS_SIMULATION_RESULT_H
#define SOPHIA_MONTE_CARLO_MODELS_SIMULATION_RESULT_H

#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Interface for the result of a simulation (rollout) in MCTS.
     *
     * This is a marker interface. Specific games should implement this to carry
     * whatever data they need from a simulation (e.g., winner, final score, etc.).
     * The interpretation of this data into a reward value is done by the Node's
     * interpret_result method.
     */
    class SimulationResult
    {
    public:
        virtual ~SimulationResult() = default;

        [[nodiscard]] virtual double reward() const = 0;
    };

    /**
     * @brief A simple, concrete implementation of SimulationResult that stores a reward.
     * Useful for generic or simpler MCTS applications.
     */
    class SimpleSimulationResult : public SimulationResult
    {
    public:
        explicit SimpleSimulationResult(double reward);
        ~SimpleSimulationResult() override = default;

        [[nodiscard]] double reward() const override;

    private:
        double m_reward_;
    };
}

#endif // SOPHIA_MONTE_CARLO_MODELS_SIMULATION_RESULT_H
