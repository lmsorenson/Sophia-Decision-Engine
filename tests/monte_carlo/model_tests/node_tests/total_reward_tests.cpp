#include <gtest/gtest.h>
#include <mock_node.h>
#include "monte_carlo_nodes_fixture.h"
#include "logging/console_logger.h"

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_total_reward_default_value_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::ERROR);

        const auto n = MockNode("name 1", nullptr, test_logger);

        const auto total_reward = n.total_reward();

        EXPECT_EQ(total_reward, 0);
    }

    TEST_F(MonteCarloModelsFixture, node_total_reward_with_non_default_value_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::ERROR);
        auto n = MockNode("name 1", nullptr, test_logger);

        n.SetTotalReward(30);

        const auto total_reward = n.total_reward();

        EXPECT_EQ(total_reward, 30);
    }
}

