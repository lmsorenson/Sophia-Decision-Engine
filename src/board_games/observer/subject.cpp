#include <board_games/observer/subject.h>

namespace sophia::board_games::observer
{
    void Subject::add_observer(const std::shared_ptr<Observer>& observer)
    {
        if (observer)
        {
            m_observers.push_back(observer);
        }
    }

    void Subject::notify(const std::string& message) const
    {
        for (const auto& observer : m_observers)
        {
            if (observer)
            {
                observer->update(message);
            }
        }
    }
}
