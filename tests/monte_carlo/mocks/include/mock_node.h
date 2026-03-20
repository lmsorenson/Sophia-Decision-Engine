#ifndef MOCK_NODE_H
#define MOCK_NODE_H

#include <gmock/gmock.h>
#include <monte_carlo/factories/tree_factory_interface.h>
#include <monte_carlo/models/node_base.h>
#include <logging/ilogger.h> // Added include for ILogger


namespace sophia::monte_carlo::models
{
    class RolloutStrategyInterface;
}

namespace sophia::monte_carlo::mocks
{
    using models::NodeBase;
    using models::Action;
    using models::RolloutStrategyInterface;
    using factories::TreeFactoryBase;
    using std::string;
    using std::vector;
    using std::make_shared;
    using std::shared_ptr;

    class MockNode : public NodeBase<bool, int>
    {
    public:
        explicit MockNode(const string& name, const shared_ptr<const TreeFactoryBase<bool, int>>& interface, const logger_ptr& logger);
        ~MockNode() override = default;

        MOCK_METHOD(vector<shared_ptr<Action>>, get_available_actions, (), (override));
        MOCK_METHOD(bool, is_terminal_state, (), (const, override));
        MOCK_METHOD(const_simulation_result_ptr, value, (), (const, override));
        MOCK_METHOD(void, print, (), (const, override));
        MOCK_METHOD(shared_ptr<Action>, select_action, (std::string action_name), (override));

        void Setup(const vector<shared_ptr<Node>> &node_expansion);
        void Setup(double value ) const;

        std::shared_ptr<const Action> GetParent() const;
        void SetVisitCount(int newVisitCount);
        void SetTotalReward(double newTotalReward);
    };
}

#endif //MOCK_NODE_H
