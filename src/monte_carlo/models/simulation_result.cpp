#include <monte_carlo/models/simulation_result.h>

using sophia::monte_carlo::models::SimulationResult;

SimulationResult::SimulationResult(const double reward)
    : m_reward_(reward)
{
}

double SimulationResult::Reward() const
{
    return m_reward_;
}
