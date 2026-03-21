#ifndef SOPHIA_SIMULATION_ACTION_H
#define SOPHIA_SIMULATION_ACTION_H

#include <string>

namespace sophia::simulation::interfaces
{
    /**
     * @class SimulationAction
     * @brief Interface for a single action (move) in a simulation.
     */
    class SimulationAction
    {
    public:
        virtual ~SimulationAction();

        /**
         * @brief Returns a human-readable name for the action (e.g., "A1").
         */
        [[nodiscard]] virtual std::string name() const = 0;
    };
}

#endif //SOPHIA_SIMULATION_ACTION_H
