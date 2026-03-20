#ifndef SOPHIA_TIC_TAC_TOE_OBSERVER_SUBJECT_H
#define SOPHIA_TIC_TAC_TOE_OBSERVER_SUBJECT_H
#include <tic_tac_toe/observer/observer.h>
#include <memory>
#include <vector>

#include <tic_tac_toe/common_aliases.h>

namespace sophia::monte_carlo::tic_tac_toe::observer
{
    /**
     * @class Subject
     * @brief The subject in an observer pattern.
     */
    class Subject
    {
    public:
        /**
         * @brief Adds an observer to the subject.
         * @param observer The observer to add.
         */
        void add_observer(const observer_ptr& observer);

        /**
         * @brief Notifies the Subject's Observers with a given message.
         * @param message The message to send to the Observers.
         */
        void notify(std::string message) const;

    private:
        std::vector<std::shared_ptr<Observer>> observers_;
    };
}

#endif // SOPHIA_TIC_TAC_TOE_OBSERVER_SUBJECT_H
