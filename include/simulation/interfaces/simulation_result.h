#ifndef SOPHIA_SIMULATION_RESULT_H
#define SOPHIA_SIMULATION_RESULT_H

#include <vector>
#include <memory>

namespace sophia::simulation::interfaces
{
    /**
     * @class SimulationResult
     * @brief Interface for the outcome of a simulation or game.
     */
    class SimulationResult
    {
    public:
        virtual ~SimulationResult() = default;

        /**
         * @brief Returns the reward/score for a given player or team.
         */
        [[nodiscard]] virtual double get_reward(int player_id) const = 0;

        /**
         * @brief Whether the simulation ended in a terminal state (win/loss/draw).
         */
        [[nodiscard]] virtual bool is_terminal() const = 0;
    };
}

#endif //SOPHIA_SIMULATION_RESULT_H
