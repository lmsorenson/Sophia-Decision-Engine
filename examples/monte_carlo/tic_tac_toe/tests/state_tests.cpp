#include <gtest/gtest.h>
#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <monte_carlo/models/node.h>
#include <tic_tac_toe/models/bot.h>
#include <logging/console_logger.h>
#include <logging/ilogger.h>

namespace sophia::monte_carlo::tic_tac_toe::model_tests
{
    using std::dynamic_pointer_cast;
    using std::shared_ptr;
    using std::make_shared;
    using std::vector;

    class TicTacToeModelsFixture : public ::testing::Test
    {
    };

    TEST_F(TicTacToeModelsFixture, test)
    {
        auto test_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::ERROR);

        auto bot = std::make_shared<models::Bot>(enums::Symbol::X, 1, test_logger);
        const auto factory = make_shared<factories::TicTacToeFactory>(nullptr, bot, test_logger);

        auto node = factory->CreateNode("S0");

        auto value = node->Value();

        EXPECT_EQ(1,1);
    }
}