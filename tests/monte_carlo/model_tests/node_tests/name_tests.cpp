#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>

#include "logging/console_logger.h"

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_name_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::Error);
        const auto n = MockNode("name 1", nullptr, test_logger);

        const auto name = n.name();

        EXPECT_EQ(name, "name 1");
    }
}

