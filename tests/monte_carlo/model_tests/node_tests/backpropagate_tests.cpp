#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/simulation_result.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockNode;
    using models::SimulationResult;
    using std::make_shared;

    TEST_F(MonteCarloModelsFixture, node_backpropagate_test)
    {
        auto factory = std::make_shared<mocks::MockTreeFactory>();

        auto s1 = factory->CreateNode("S1");
        auto s2 = factory->CreateNode("S2");
        auto s1_ = std::static_pointer_cast<MockNode>(s1);
        auto a1 = factory->CreateAction(s1_, 1);
        s2->SetParent(a1);

        s1->Backpropagate(make_shared<SimulationResult>(10));
        s2->Backpropagate(make_shared<SimulationResult>(10));
        s2->Backpropagate(make_shared<SimulationResult>(10));

        const auto actualVisitCountS1 = s1->VisitCount();
        const auto actualTotalRewardS1 = s1->TotalReward();
        const auto actualVisitCountS2 = s2->VisitCount();
        const auto actualTotalRewardS2 = s2->TotalReward();

        EXPECT_EQ(actualVisitCountS1, 3);
        EXPECT_EQ(actualTotalRewardS1, 30);
        EXPECT_EQ(actualVisitCountS2, 2);
        EXPECT_EQ(actualTotalRewardS2, 20);
    }

    TEST_F(MonteCarloModelsFixture, node_backpropagate_null_reward_test)
    {
        auto factory = std::make_shared<mocks::MockTreeFactory>();
        auto s1 = factory->CreateNode("S1");

        // Backpropagate with null reward should increment visit count but add 0 to total reward
        s1->Backpropagate(nullptr);

        EXPECT_EQ(s1->VisitCount(), 1);
        EXPECT_EQ(s1->TotalReward(), 0.0);
    }
}

