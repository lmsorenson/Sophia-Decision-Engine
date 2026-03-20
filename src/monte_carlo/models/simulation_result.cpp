#include <monte_carlo/models/simulation_result.h>

using sophia::monte_carlo::models::SimpleSimulationResult;

SimpleSimulationResult::SimpleSimulationResult(double reward)
    : m_reward_(reward)
{
}

double SimpleSimulationResult::Reward() const
{
    return m_reward_;
}
