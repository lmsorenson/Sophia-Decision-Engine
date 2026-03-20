#include <gtest/gtest.h>
#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <monte_carlo/models/node.h>
#include <tic_tac_toe/models/game.h>
#include <monte_carlo/tree_search_algorithm.h>
#include <tic_tac_toe/models/bot.h>
#include <logging/console_logger.h>
#include <logging/ilogger.h>

namespace sophia::monte_carlo::tic_tac_toe::model_tests
{
    using models::Game;
    using logging::ConsoleLogger;
    using logging::LogLevel;
    using std::dynamic_pointer_cast;
    using std::shared_ptr;
    using std::make_shared;
    using std::vector;

    class TicTacToeModelsFixture : public ::testing::Test
    {
    };

    TEST_F(TicTacToeModelsFixture, simulation_test)
    {
        auto test_logger = std::make_shared<ConsoleLogger>(LogLevel::ERROR);
        const shared_ptr<Game> game = make_shared<Game>(test_logger);

        game->Assign<models::Bot>(enums::Symbol::X, 1, factories::RolloutStrategyType::Heuristic);
        game->Assign<models::Bot>(enums::Symbol::O, 1, factories::RolloutStrategyType::Heuristic);
        auto bot = game->get_player(enums::Symbol::X);

        const auto factory = make_shared<factories::TicTacToeFactory>(game, bot, test_logger);

        const auto node = factory->CreateNode("S0");

        MonteCarloTreeSearch::run(node, 10, test_logger);

        EXPECT_EQ(1,1);
    }
}

