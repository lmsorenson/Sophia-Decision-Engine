#include "monte_carlo_action_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/action.h>
#include <mock_node.h>
#include <mock_action.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloActionFixture, action_upper_confidence_bound_null_nodes_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto a1 = factory->CreateAction(nullptr, 1);

        const auto ucb = a1->upper_confidence_bound(2);

        EXPECT_EQ(ucb, 0.0);
    }

    TEST_F(MonteCarloActionFixture, action_upper_confidence_bound_infinity_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        auto s1_ = std::static_pointer_cast<MockNode>(s1);
        const auto a1 = factory->CreateAction(s1_, 1);
        std::dynamic_pointer_cast<mocks::MockAction>(a1)->Setup("S2", s2);

        std::dynamic_pointer_cast<MockNode>(s1)->SetTotalReward(0);
        std::dynamic_pointer_cast<MockNode>(s1)->SetVisitCount(0);

        const auto ucb = a1->upper_confidence_bound(2);

        EXPECT_EQ(ucb, std::numeric_limits<double>::infinity());
    }

    TEST_F(MonteCarloActionFixture, action_upper_confidence_bound_value_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        auto s1_ = std::static_pointer_cast<MockNode>(s1);
        const auto a1 = factory->CreateAction(s1_, 1);

        std::dynamic_pointer_cast<mocks::MockAction>(a1)->Setup("S2", s2);

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2 });
        s1->expand();
        std::dynamic_pointer_cast<MockNode>(s1)->SetTotalReward(20);
        std::dynamic_pointer_cast<MockNode>(s1)->SetVisitCount(1);
        std::dynamic_pointer_cast<MockNode>(s2)->SetTotalReward(20);
        std::dynamic_pointer_cast<MockNode>(s2)->SetVisitCount(1);

        const auto ucb = a1->upper_confidence_bound(2);

        EXPECT_EQ(ucb, 20);
    }
}

