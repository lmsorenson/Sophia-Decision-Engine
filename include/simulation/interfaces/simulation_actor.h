#ifndef SOPHIA_SIMULATION_ACTOR_H
#define SOPHIA_SIMULATION_ACTOR_H

#include <memory>
#include <simulation/interfaces/simulation_state.h>
#include <simulation/interfaces/simulation_action.h>

namespace sophia::simulation::interfaces
{
    /**
     * @class SimulationActor
     * @brief Interface for an entity that can perform actions in a simulation.
     */
    class SimulationActor
    {
    public:
        virtual ~SimulationActor();

        /**
         * @brief Returns the ID of the player this actor represents.
         */
        [[nodiscard]] virtual PlayerId player_id() const = 0;

        /**
         * @brief Returns the action to perform from the given state.
         */
        [[nodiscard]] virtual std::shared_ptr<SimulationAction> decide_action(const std::shared_ptr<SimulationState>& current_state) = 0;
    };
}

#endif //SOPHIA_SIMULATION_ACTOR_H
