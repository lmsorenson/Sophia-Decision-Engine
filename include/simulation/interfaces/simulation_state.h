#ifndef SOPHIA_SIMULATION_STATE_H
#define SOPHIA_SIMULATION_STATE_H

#include <vector>
#include <memory>
#include <simulation/interfaces/simulation_action.h>
#include <simulation/interfaces/simulation_result.h>

namespace sophia::simulation::interfaces
{
    using PlayerId = int;

    /**
     * @class SimulationState
     * @brief Interface for a state in the simulation.
     */
    class SimulationState
    {
    public:
        virtual ~SimulationState();

        /**
         * @brief Returns a list of all legal actions from the current state.
         */
        [[nodiscard]] virtual std::vector<std::shared_ptr<SimulationAction>> get_legal_actions() const = 0;

        /**
         * @brief Returns a new state resulting from applying the given action to this state.
         */
        [[nodiscard]] virtual std::shared_ptr<SimulationState> apply_action(const std::shared_ptr<SimulationAction>& action) const = 0;

        /**
         * @brief Returns the ID of the player whose turn it is to act.
         */
        [[nodiscard]] virtual PlayerId current_player_id() const = 0;

        /**
         * @brief Whether this state is a terminal state.
         */
        [[nodiscard]] virtual bool is_terminal() const = 0;

        /**
         * @brief Returns the result of the simulation if it's terminal.
         */
        [[nodiscard]] virtual std::shared_ptr<SimulationResult> get_result() const = 0;
    };
}

#endif //SOPHIA_SIMULATION_STATE_H
