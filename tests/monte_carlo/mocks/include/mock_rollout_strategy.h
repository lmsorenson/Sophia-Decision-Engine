#ifndef SOPHIA_TESTS_MONTE_CARLO_MOCKS_MOCK_ROLLOUT_STRATEGY_H
#define SOPHIA_TESTS_MONTE_CARLO_MOCKS_MOCK_ROLLOUT_STRATEGY_H

#include <gmock/gmock.h>
#include <monte_carlo/models/rollout_strategy_interface.h>


namespace sophia::monte_carlo::mocks
{
    using models::RolloutStrategyInterface;
    using models::Action;
    using std::shared_ptr;
    using std::vector;

    class MockRolloutStrategy : public RolloutStrategyInterface
    {
    public:
        [[nodiscard]] shared_ptr<Action> select_action(std::vector<std::shared_ptr<Action>> actions) const override;
    };
}

#endif // SOPHIA_TESTS_MONTE_CARLO_MOCKS_MOCK_ROLLOUT_STRATEGY_H
