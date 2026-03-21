#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <mock_node.h>
#include <mock_tree_factory.h>
#include <logging/console_logger.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using mocks::MockNode;

    TEST_F(MonteCarloModelsFixture, node_upper_confidence_bound_infinity_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        const auto factory = std::make_shared<MockTreeFactory>(test_logger);
        const auto s1 = factory->CreateNode("S1");

        std::dynamic_pointer_cast<MockNode>(s1)->SetTotalReward(0);
        std::dynamic_pointer_cast<MockNode>(s1)->SetVisitCount(0);

        const auto ucb = s1->upper_confidence_bound(2);

        EXPECT_EQ(ucb, std::numeric_limits<double>::infinity());
    }

    TEST_F(MonteCarloModelsFixture, node_upper_confidence_bound_value_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        const auto factory = std::make_shared<MockTreeFactory>(test_logger);
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        s1->expand();
        std::dynamic_pointer_cast<MockNode>(s1)->SetTotalReward(20);
        std::dynamic_pointer_cast<MockNode>(s1)->SetVisitCount(1);
        std::dynamic_pointer_cast<MockNode>(s2)->SetTotalReward(20);
        std::dynamic_pointer_cast<MockNode>(s2)->SetVisitCount(1);

        const auto ucb = s2->upper_confidence_bound(3);

        EXPECT_EQ(ucb, 20);
    }
}

