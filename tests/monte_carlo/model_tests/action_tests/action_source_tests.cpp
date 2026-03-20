#include "monte_carlo_action_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/action.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloActionFixture, action_source_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        auto s1_ = std::static_pointer_cast<MockNode>(s1);
        const auto a1 = factory->CreateAction(s1_, 1);

        const auto actual_source = a1->source();

        EXPECT_NE(actual_source, nullptr);
    }

    TEST_F(MonteCarloActionFixture, action_source_null_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto a1 = factory->CreateAction(nullptr, 1);

        const auto actual_source = a1->source();

        EXPECT_EQ(actual_source, nullptr);
    }
}

