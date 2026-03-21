#ifndef SOPHIA_BOARD_GAMES_SUBJECT_H
#define SOPHIA_BOARD_GAMES_SUBJECT_H

#include <vector>
#include <memory>
#include <string>
#include <board_games/observer/observer.h>

namespace sophia::board_games::observer
{
    /**
     * @class Subject
     * @brief Base class for a subject in the Observer pattern.
     */
    class Subject
    {
    public:
        virtual ~Subject() = default;

        void add_observer(const std::shared_ptr<Observer>& observer);

        void notify(const std::string& message) const;

    private:
        std::vector<std::shared_ptr<Observer>> m_observers;
    };
}

#endif //SOPHIA_BOARD_GAMES_SUBJECT_H
