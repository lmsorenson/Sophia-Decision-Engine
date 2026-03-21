#ifndef SOPHIA_SIMULATION_RUNNER_H
#define SOPHIA_SIMULATION_RUNNER_H

#include <memory>
#include <map>
#include <simulation/interfaces/simulation_state.h>
#include <simulation/interfaces/simulation_actor.h>
#include <board_games/observer/subject.h>
#include <board_games/common_aliases.h>

namespace sophia::simulation::models
{
    using namespace interfaces;

    /**
     * @class SimulationRunner
     * @brief A generic engine to run a simulation from start to finish.
     */
    class SimulationRunner : public board_games::observer::Subject
    {
    public:
        explicit SimulationRunner(board_games::logger_ptr logger);

        /**
         * @brief Registers an actor for a specific player ID.
         */
        void add_actor(std::shared_ptr<SimulationActor> actor);

        /**
         * @brief Runs the simulation until a terminal state is reached.
         * @param initial_state The starting state of the simulation.
         * @return The final result of the simulation.
         */
        std::shared_ptr<SimulationResult> run(std::shared_ptr<SimulationState> initial_state);

    private:
        board_games::logger_ptr m_logger;
        std::map<PlayerId, std::shared_ptr<SimulationActor>> m_actors;
    };
}

#endif //SOPHIA_SIMULATION_RUNNER_H
