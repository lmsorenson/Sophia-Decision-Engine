#include <gtest/gtest.h>
#include <monte_carlo/tree_search_algorithm.h>
#include <mock_tree_factory.h>
#include <mock_node.h>
#include <logging/console_logger.h>
#include <logging/ilogger.h>
#include <monte_carlo/models/action.h> // Required for full definition of Action
#include <monte_carlo/common_aliases.h> // For action_ptr, const_action_ptr, logger_ptr

namespace sophia::monte_carlo::tree_search_algorithm_tests
{
    using mocks::MockNode;
    using mocks::MockTreeFactory;
    using models::Node;
    using std::dynamic_pointer_cast;
    using std::shared_ptr;
    using std::make_shared;
    using std::vector;

    class MonteCarloTreeSearchFixture : public ::testing::Test
    {
    };

    TEST_F(MonteCarloTreeSearchFixture, tree_search_algorithm_test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::Error);

        const auto factory = make_shared<MockTreeFactory>();
        const auto s0 = factory->CreateNode("s0");
        auto s1 = factory->CreateNode("s1");
        auto s2 = factory->CreateNode("s2");
        auto s3 = factory->CreateNode("s3");
        auto s4 = factory->CreateNode("s4");
        auto s5 = factory->CreateNode("s5");
        auto s6 = factory->CreateNode("s6");

        dynamic_pointer_cast<MockNode>(s0)->Setup({ s1, s2 });
        dynamic_pointer_cast<MockNode>(s1)->Setup({ s3, s4 });
        dynamic_pointer_cast<MockNode>(s1)->Setup(20);
        dynamic_pointer_cast<MockNode>(s2)->Setup({ s5, s6 });
        dynamic_pointer_cast<MockNode>(s2)->Setup(10);
        dynamic_pointer_cast<MockNode>(s3)->Setup(0);
        dynamic_pointer_cast<MockNode>(s5)->Setup(14);

        // the tree starts with two actions?
        s0->expand();
        const action_ptr best_decision = MonteCarloTreeSearch::run(s0, 4, test_logger);

        auto name = best_decision->name();

        EXPECT_EQ(name, "s2");
    }
}

