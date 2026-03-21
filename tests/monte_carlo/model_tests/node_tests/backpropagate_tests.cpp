#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/simulation_result.h>
#include <mock_node.h>
#include <mock_tree_factory.h>
#include <logging/console_logger.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;
    using models::SimpleSimulationResult;
    using std::make_shared;

    TEST_F(MonteCarloModelsFixture, node_backpropagate_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        auto factory = std::make_shared<mocks::MockTreeFactory>(test_logger);

        auto s1 = factory->CreateNode("S1");
        auto s2 = factory->CreateNode("S2");
        auto s1_ = std::static_pointer_cast<MockNode>(s1);
        auto a1 = factory->CreateAction(s1_, 1);
        s2->set_parent(a1);

        s1->backpropagate(make_shared<SimpleSimulationResult>(10));
        s2->backpropagate(make_shared<SimpleSimulationResult>(10));
        s2->backpropagate(make_shared<SimpleSimulationResult>(10));

        const auto actualVisitCountS1 = s1->visit_count();
        const auto actualTotalRewardS1 = s1->total_reward();
        const auto actualVisitCountS2 = s2->visit_count();
        const auto actualTotalRewardS2 = s2->total_reward();

        EXPECT_EQ(actualVisitCountS1, 3);
        EXPECT_EQ(actualTotalRewardS1, 30);
        EXPECT_EQ(actualVisitCountS2, 2);
        EXPECT_EQ(actualTotalRewardS2, 20);
    }

    TEST_F(MonteCarloModelsFixture, node_backpropagate_null_reward_test)
    {
        auto test_logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::Error);

        auto factory = std::make_shared<mocks::MockTreeFactory>(test_logger);
        auto s1 = factory->CreateNode("S1");

        // backpropagate with null reward should increment visit count but add 0 to total reward
        s1->backpropagate(nullptr);

        EXPECT_EQ(s1->visit_count(), 1);
        EXPECT_EQ(s1->total_reward(), 0.0);
    }
}

