#include <gtest/gtest.h>
#include <mock_node.h>
#include "monte_carlo_nodes_fixture.h"
#include "logging/console_logger.h"

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_value_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::ERROR);

        const auto n = MockNode("name 1", nullptr, test_logger);
        n.Setup(0);

        const auto result = n.value();

        EXPECT_EQ(result->reward(), 0);
    }
}

