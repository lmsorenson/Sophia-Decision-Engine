#include <simulation/models/simulation_runner.h>
#include <utility>

namespace sophia::simulation::models
{
    SimulationRunner::SimulationRunner(board_games::logger_ptr logger) 
        : m_logger(std::move(logger)) 
    {}

    void SimulationRunner::add_actor(std::shared_ptr<SimulationActor> actor)
    {
        if (actor)
        {
            m_actors[actor->player_id()] = std::move(actor);
        }
    }

    std::shared_ptr<SimulationResult> SimulationRunner::run(std::shared_ptr<SimulationState> initial_state)
    {
        auto current_state = std::move(initial_state);

        while (current_state && !current_state->is_terminal())
        {
            PlayerId pid = current_state->current_player_id();
            auto actor_it = m_actors.find(pid);

            if (actor_it == m_actors.end())
            {
                if (m_logger) m_logger->error("No actor registered for player ID {}", pid);
                break;
            }

            notify("Player " + std::to_string(pid) + " is thinking...");
            
            auto action = actor_it->second->decide_action(current_state);
            if (!action)
            {
                if (m_logger) m_logger->error("Actor for player {} failed to provide an action", pid);
                break;
            }

            notify("Player " + std::to_string(pid) + " chose action: " + action->name());
            current_state = current_state->apply_action(action);
        }

        auto final_result = current_state ? current_state->get_result() : nullptr;
        if (final_result)
        {
            notify("Simulation complete.");
        }
        
        return final_result;
    }
}
