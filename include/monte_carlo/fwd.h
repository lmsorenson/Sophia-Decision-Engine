#ifndef SOPHIA_MONTE_CARLO_FWD_H
#define SOPHIA_MONTE_CARLO_FWD_H

namespace sophia::monte_carlo::models
{
    class Action;
    class Node;
    class RolloutStrategyInterface;
    class SimulationResult;
    template<typename TState, typename TChange> class NodeBase;
    // Add other core model forward declarations here if needed
}

namespace sophia::monte_carlo::factories
{
    template<typename TState, typename TChange> class TreeFactoryBase;
}

#endif // SOPHIA_MONTE_CARLO_FWD_H
