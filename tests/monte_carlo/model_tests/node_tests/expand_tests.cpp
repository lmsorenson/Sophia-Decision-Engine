#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_tree_factory.h>
#include <mock_node.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_expand_with_no_available_actions_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");

        const auto first_node = s1->expand();

        EXPECT_EQ(first_node, nullptr);
    }

    TEST_F(MonteCarloModelsFixture, node_expand_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");
        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });

        const auto first_node = s1->expand();

        EXPECT_EQ(first_node->name(), "S2");
    }
}

