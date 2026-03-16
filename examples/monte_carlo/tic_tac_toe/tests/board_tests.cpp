#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tic_tac_toe/models/board.h>
#include <tic_tac_toe/models/position.h>
#include <logging/console_logger.h>

namespace sophia::monte_carlo::tic_tac_toe::model_tests
{
    using models::Board;
    using models::Position;
    using enums::Symbol;

    TEST(BoardTests, to_mask_returns_correct_bits)
    {
        // Arrange
        auto logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::ERROR);
        Board board(logger);

        // X at (0,0) index 0, bit 1
        // O at (1,1) index 4, bit 16
        // X at (2,2) index 8, bit 256
        board.SetPosition(Position({0, 0}, Symbol::X));
        board.SetPosition(Position({1, 1}, Symbol::O));
        board.SetPosition(Position({2, 2}, Symbol::X));

        // Act
        auto mask = board.ToMask();

        // Assert
        EXPECT_EQ(mask.x_mask, (1 << 0) | (1 << 8)); // 1 + 256 = 257
        EXPECT_EQ(mask.o_mask, (1 << 4));            // 16
    }

    TEST(BoardTests, to_mask_empty_board)
    {
        // ... (previous test code)
    }

    TEST(BoardTests, get_winning_moves_finds_single_win)
    {
        // Arrange
        auto logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::ERROR);
        Board board(logger);

        // X has A1, A2. Should win at A3 (0,2)
        board.SetPosition(Position({0, 0}, Symbol::X));
        board.SetPosition(Position({0, 1}, Symbol::X));
        
        // Act
        auto wins = board.GetWinningMoves(Symbol::X);

        // Assert
        ASSERT_EQ(wins.size(), 1);
        EXPECT_EQ(wins[0]->Name(), "A3");
    }

    TEST(BoardTests, get_winning_moves_finds_multiple_wins)
    {
        // Arrange
        auto logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::ERROR);
        Board board(logger);

        // X has A1, B2. Winning moves are C3 (diagonal)
        // Also X has A1, A2. Winning move A3.
        board.SetPosition(Position({0, 0}, Symbol::X)); // A1
        board.SetPosition(Position({1, 1}, Symbol::X)); // B2
        board.SetPosition(Position({0, 1}, Symbol::X)); // A2
        
        // Act
        auto wins = board.GetWinningMoves(Symbol::X);

        // Assert
        // Wins: 
        // 1. A3 (row 0: A1, A2)
        // 2. C3 (main diagonal: A1, B2)
        // 3. C1 (column 0: A1 is at 0,0. Wait, X has A1 and B2.)
        // Let's re-verify:
        // X has A1(0,0), B2(1,1), A2(0,1)
        // Row 0: A1, A2 -> Win at A3
        // Col 0: A1 -> No win
        // Col 1: A2, B2 -> Win at C2 (2,1)
        // Diag: A1, B2 -> Win at C3 (2,2)
        
        ASSERT_EQ(wins.size(), 3);
        std::vector<std::string> names = {wins[0]->Name(), wins[1]->Name(), wins[2]->Name()};
        EXPECT_THAT(names, ::testing::UnorderedElementsAre("A3", "C2", "C3"));
    }

    TEST(BoardTests, get_winning_moves_ignores_blocked_wins)
    {
        // Arrange
        auto logger = std::make_shared<logging::ConsoleLogger>(logging::LogLevel::ERROR);
        Board board(logger);

        // X has A1, A2. But O has A3.
        board.SetPosition(Position({0, 0}, Symbol::X));
        board.SetPosition(Position({0, 1}, Symbol::X));
        board.SetPosition(Position({0, 2}, Symbol::O));
        
        // Act
        auto wins = board.GetWinningMoves(Symbol::X);

        // Assert
        EXPECT_TRUE(wins.empty());
    }
}