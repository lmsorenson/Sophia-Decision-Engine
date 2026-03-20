#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_has_been_sampled_false_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");

        const auto has_been_sampled = s1->has_been_sampled();

        EXPECT_EQ(has_been_sampled, false);
    }

    TEST_F(MonteCarloModelsFixture, node_has_been_sampled_true_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        std::dynamic_pointer_cast<MockNode>(s1)->SetVisitCount(1);

        const auto has_been_sampled = s1->has_been_sampled();

        EXPECT_EQ(has_been_sampled, true);
    }
}
