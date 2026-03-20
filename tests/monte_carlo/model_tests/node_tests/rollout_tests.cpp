#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>
#include <mock_tree_factory.h>
#include <monte_carlo/models/simulation_result.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;
    using models::SimpleSimulationResult;
    using std::make_shared;

    TEST_F(MonteCarloModelsFixture, node_rollout_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1_base = factory->CreateNode("S1");
        auto s1 = std::dynamic_pointer_cast<MockNode>(s1_base); // Cast to MockNode

        EXPECT_CALL(*s1, IsTerminalState())
            .WillRepeatedly(::testing::Return(true));
        EXPECT_CALL(*s1, Value())
            .WillRepeatedly(::testing::Return(make_shared<SimpleSimulationResult>(-1.0)));

        const auto result = s1->Rollout();

        EXPECT_EQ(result->Reward(), -1);
    }

    TEST_F(MonteCarloModelsFixture, node_rollout_2_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        auto s2 = factory->CreateNode("S2");
        auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        std::dynamic_pointer_cast<MockNode>(s2)->Setup(20);
        s1->Expand();

        const auto result = s1->Rollout();

        EXPECT_EQ(result->Reward(), 20);
    }
}

