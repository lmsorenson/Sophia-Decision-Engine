#ifndef SIMULATION_RESULT_H
#define SIMULATION_RESULT_H

#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Represents the result of a simulation (rollout) in MCTS.
     *
     * This class encapsulates the information gathered during a simulation,
     * such as the reward obtained and potentially other metrics or terminal state info.
     */
    class SimulationResult
    {
    public:
        explicit SimulationResult(double reward);
        virtual ~SimulationResult() = default;

        /**
         * @brief Gets the reward obtained from the simulation.
         * @return The simulation reward.
         */
        [[nodiscard]] double Reward() const;

    private:
        double m_reward_;
    };
}

#endif //SIMULATION_RESULT_H
