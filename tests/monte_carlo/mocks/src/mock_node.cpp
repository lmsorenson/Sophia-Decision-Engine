#include <mock_action.h>
#include <mock_node.h>

#include <monte_carlo/factories/tree_factory_interface.h>
#include <monte_carlo/models/simulation_result.h>
#include <logging/ilogger.h>

using sophia::monte_carlo::mocks::MockNode;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::models::Action;
using sophia::monte_carlo::factories::TreeFactoryBase;
using sophia::monte_carlo::models::SimulationResult;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;
using testing::Return;

MockNode::MockNode(const string& name, const shared_ptr<const TreeFactoryBase<bool, int>>& interface, const logger_ptr& logger)
    : NodeBase(std::move(name), true, std::move(interface), logger)
{
}

void MockNode::Setup(const vector<shared_ptr<Node>> &node_expansion )
{
    vector<shared_ptr<Action>> actions = {};
    actions.reserve(node_expansion.size());

    for(const auto& node : node_expansion)
    {
        auto _this_ = std::static_pointer_cast<MockNode>(shared_from_this());
        auto action = m_factory_->CreateAction(_this_, 1);
        const auto ma = std::dynamic_pointer_cast<MockAction>(action);
        ma->Setup(node->Name(), node);
        actions.push_back(action);
    }

    EXPECT_CALL(*this, GetAvailableActions())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(actions));
}

void MockNode::Setup( const double value ) const
{
    EXPECT_CALL(*this, IsTerminalState())
                .Times(::testing::AnyNumber())
                .WillOnce(Return(true))
                .WillOnce(Return(false));
    EXPECT_CALL(*this, Value())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(make_shared<SimulationResult>(value)));
}

std::shared_ptr<const Action> MockNode::GetParent() const
{
    return m_parent_action_.lock();
}

void MockNode::SetVisitCount(const int newVisitCount)
{
    m_visit_count_ = newVisitCount;
}

void MockNode::SetTotalReward(const double newTotalReward)
{
    m_total_reward_ = newTotalReward;
}



