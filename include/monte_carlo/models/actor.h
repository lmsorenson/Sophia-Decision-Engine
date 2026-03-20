#ifndef SOPHIA_MONTE_CARLO_MODELS_ACTOR_H
#define SOPHIA_MONTE_CARLO_MODELS_ACTOR_H

#include <monte_carlo/common_aliases.h>

namespace sophia::monte_carlo::models
{
    /**
     * @brief Represents an actor in the Monte Carlo Tree Search.
     */
    class Actor
    {
    public:
        Actor() = default;
        virtual ~Actor() = default;
    };
}

#endif // SOPHIA_MONTE_CARLO_MODELS_ACTOR_H
