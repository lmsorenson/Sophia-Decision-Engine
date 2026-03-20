#include "monte_carlo_nodes_fixture.h"
#include <gtest/gtest.h>
#include <monte_carlo/models/action.h>
#include <monte_carlo/models/simulation_result.h>
#include <mock_node.h>
#include <mock_tree_factory.h>

namespace sophia::monte_carlo::model_tests
{
    using mocks::MockTreeFactory;
    using models::SimpleSimulationResult;
    using mocks::MockNode;
    using std::make_shared;

    TEST_F(MonteCarloModelsFixture, node_select_best_action_no_scores_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        s1->expand();

        const auto best_action = s1->select_best_action();
        const auto best_node = best_action->target();

        EXPECT_EQ(best_node->name(), "S2");
    }

    TEST_F(MonteCarloModelsFixture, node_select_best_action_choose_node_with_no_scores_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        s1->expand();
        s2->backpropagate(make_shared<SimpleSimulationResult>(20));

        const auto best_action = s1->select_best_action();
        const auto best_node = best_action->target();

        EXPECT_EQ(best_node->name(), "S3");
    }

    TEST_F(MonteCarloModelsFixture, node_select_best_action_choose_node_with_best_scores_test)
    {
        const auto factory = std::make_shared<MockTreeFactory>();
        const auto s1 = factory->CreateNode("S1");
        const auto s2 = factory->CreateNode("S2");
        const auto s3 = factory->CreateNode("S3");

        std::dynamic_pointer_cast<MockNode>(s1)->Setup({ s2, s3 });
        s1->expand();
        s2->backpropagate(make_shared<SimpleSimulationResult>(20));
        s3->backpropagate(make_shared<SimpleSimulationResult>(30));

        const auto best_action = s1->select_best_action();
        const auto best_node = best_action->target();

        EXPECT_EQ(best_node->name(), "S3");
    }
}

