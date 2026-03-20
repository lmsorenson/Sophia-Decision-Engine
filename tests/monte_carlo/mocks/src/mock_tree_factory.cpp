#include <mock_tree_factory.h>
#include <monte_carlo/models/rollout_strategy_interface.h>
#include <mock_node.h>
#include <mock_action.h>
#include <mock_rollout_strategy.h>
#include <memory>
#include <logging/ilogger.h> // Include for logger_ptr

using sophia::monte_carlo::mocks::MockTreeFactory;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::models::Action;
using sophia::monte_carlo::models::RolloutStrategyInterface;
using std::shared_ptr;
using std::make_shared;
using std::string;


shared_ptr<Node> MockTreeFactory::CreateNode(string name) const
{
    return make_shared<MockNode>(name, shared_from_this(), nullptr);
}

shared_ptr<Node> MockTreeFactory::CreateNode(string name, bool state) const
{
    return make_shared<MockNode>(name, shared_from_this(), nullptr);
}

shared_ptr<Action> MockTreeFactory::CreateAction(shared_ptr<NodeBase<bool, int>> node, int change) const
{
    return make_shared<MockAction>(node, shared_from_this());
}

shared_ptr<Action> MockTreeFactory::CreateAction(shared_ptr<NodeBase<bool, int>> node, int change, const const_actor_ptr& actor) const
{
    return make_shared<MockAction>(node, shared_from_this());
}

shared_ptr<RolloutStrategyInterface> MockTreeFactory::CreateStrategy() const
{
    return make_shared<MockRolloutStrategy>();
}
