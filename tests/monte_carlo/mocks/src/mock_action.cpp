#include <mock_action.h>

#include <monte_carlo/factories/tree_factory_base.h>

#include <utility>

using sophia::monte_carlo::mocks::MockAction;
using sophia::monte_carlo::models::Node;
using sophia::monte_carlo::factories::TreeFactoryBase;
using std::shared_ptr;
using std::string;
using testing::Return;

MockAction::MockAction(node_base_ptr<bool, int> source, const const_factory_ptr<bool, int> &factory)
: ActionBase(source, 0, factory, nullptr)
{

}

void MockAction::Setup(std::string name, const shared_ptr<Node> &node) const
{
    EXPECT_CALL(*this, name())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(std::move(name)));

    EXPECT_CALL(*this, target())
        .Times(::testing::AnyNumber())
        .WillRepeatedly(Return(node));
}






