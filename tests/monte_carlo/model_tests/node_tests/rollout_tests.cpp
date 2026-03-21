#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>
#include <mock_tree_factory.h>
#include <monte_carlo/models/simulation_result.h>
#include <logging/console_logger.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;
    using models::SimpleSimulationResult;
    using std::make_shared;

    TEST_F(MonteCarloModelsFixture, node_rollout_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        const auto factory = std::make_shared<MockTreeFactory>(test_logger);
        const auto s1_base = factory->CreateNode("S1");
        auto s1 = std::dynamic_pointer_cast<MockNode>(s1_base); // Cast to MockNode

        EXPECT_CALL(*s1, is_terminal_state())
            .WillRepeatedly(::testing::Return(true));
        EXPECT_CALL(*s1, value())
            .WillRepeatedly(::testing::Return(make_shared<SimpleSimulationResult>(-1.0)));

        const auto result = s1->rollout();

        EXPECT_EQ(result->reward(), -1);
    }

    TEST_F(MonteCarloModelsFixture, node_rollout_2_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        const auto factory = std::make_shared<MockTreeFactory>(test_logger);
        const auto s1 = factory->CreateNode("S1");
        auto s2 = factory->CreateNode("S2");
        auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        std::dynamic_pointer_cast<MockNode>(s2)->Setup(20);
        s1->expand();

        const auto result = s1->rollout();

        EXPECT_EQ(result->reward(), 20);
    }
}

