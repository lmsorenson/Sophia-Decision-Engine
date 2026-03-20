#include <gtest/gtest.h>
#include <mock_node.h>
#include "monte_carlo_nodes_fixture.h"
#include "logging/console_logger.h"

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, visit_count_default_value_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::Error);

        const auto n = MockNode("name 1", nullptr, test_logger);

        const auto total_reward = n.visit_count();

        EXPECT_EQ(total_reward, 0);
    }

    TEST_F(MonteCarloModelsFixture, node_visit_count_with_non_default_value_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::Error);
        auto n = MockNode("name 1", nullptr, test_logger);

        n.SetVisitCount(3);

        const auto total_reward = n.visit_count();

        EXPECT_EQ(total_reward, 3);
    }
}

