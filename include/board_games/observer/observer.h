#ifndef SOPHIA_BOARD_GAMES_OBSERVER_H
#define SOPHIA_BOARD_GAMES_OBSERVER_H

#include <string>

namespace sophia::board_games::observer
{
    /**
     * @class Observer
     * @brief Interface for an observer in the Observer pattern.
     */
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void update(const std::string& message) = 0;
    };
}

#endif //SOPHIA_BOARD_GAMES_OBSERVER_H
