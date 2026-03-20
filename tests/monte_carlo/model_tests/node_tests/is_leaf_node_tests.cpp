#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_is_leaf_node_true_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");

        const auto is_leaf_node = s1->is_leaf_node();

        EXPECT_EQ(is_leaf_node, true);
    }

    TEST_F(MonteCarloModelsFixture, node_is_leaf_node_false_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");
        std::dynamic_pointer_cast<MockNode>(s1)->Setup({s2, s3});

        const auto is_leaf_node = s1->is_leaf_node();

        EXPECT_EQ(is_leaf_node, true);
    }
}