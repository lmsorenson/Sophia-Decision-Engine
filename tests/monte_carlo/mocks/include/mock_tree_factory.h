#ifndef MOCK_TREE_FACTORY_H
#define MOCK_TREE_FACTORY_H

#include <monte_carlo/factories/tree_factory_base.h>
#include <logging/ilogger.h>
#include <monte_carlo/common_aliases.h>


namespace sophia::monte_carlo::mocks
{
    using models::RolloutStrategyInterface;
    using factories::TreeFactoryBase;

    class MockRolloutStrategy;

    class MockTreeFactory : public TreeFactoryBase<bool, int>
    {
    public:
        explicit MockTreeFactory(const logger_ptr& logger);
        ~MockTreeFactory() override = default;

        [[nodiscard]] node_ptr CreateNode(std::string name) const override;
        [[nodiscard]] node_ptr CreateNode(std::string name, bool state) const override;
        [[nodiscard]] action_ptr CreateAction(node_base_ptr<bool, int> node, int change) const override;
        [[nodiscard]] action_ptr CreateAction(node_base_ptr<bool, int> node, int change, const const_actor_ptr& actor) const override;
        [[nodiscard]] rollout_strategy_ptr CreateStrategy() const override;
    };
}

#endif //MOCK_TREE_FACTORY_H
