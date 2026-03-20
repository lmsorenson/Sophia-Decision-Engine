#include <mock_action.h>

#include "monte_carlo_action_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/action.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloActionFixture, action_target_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto a1 = factory->CreateAction(nullptr, 1);
        std::dynamic_pointer_cast<mocks::MockAction>(a1)->Setup("S1", s1);

        const auto actual_target = a1->target();

        EXPECT_NE(actual_target, nullptr);
    }

    TEST_F(MonteCarloActionFixture, action_target_null_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto a1 = factory->CreateAction(nullptr, 1);

        const auto actual_target = a1->target();

        EXPECT_EQ(actual_target, nullptr);
    }
}

