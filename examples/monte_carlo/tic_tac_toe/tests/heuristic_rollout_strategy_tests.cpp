#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tic_tac_toe/models/heuristic_rollout_strategy.h>
#include <tic_tac_toe/models/game_state.h>
#include <tic_tac_toe/models/bot.h>
#include <tic_tac_toe/models/board.h>
#include <tic_tac_toe/models/move.h>
#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <logging/console_logger.h>
#include <logging/ilogger.h>

namespace sophia::monte_carlo::tic_tac_toe::model_tests
{
    using std::dynamic_pointer_cast;
    using std::shared_ptr;
    using std::make_shared;
    using std::vector;
    using models::HeuristicRolloutStrategy;
    using models::GameState;
    using models::Board;
    using models::Move;
    using enums::Symbol;

    class HeuristicRolloutStrategyFixture : public ::testing::Test
    {
    protected:
        const Symbol X = Symbol::X;
        const Symbol O = Symbol::O;
        const Symbol _ = Symbol::None;

        void SetUp() override
        {
            m_logger = std::make_shared<sophia::logging::ConsoleLogger>(sophia::logging::LogLevel::ERROR);
            m_playerX = std::make_shared<models::Bot>(Symbol::X, 1, m_logger);
            m_playerO = std::make_shared<models::Bot>(Symbol::O, 1, m_logger);
        }

        // Helper to create a board from a 3x3 grid
        shared_ptr<Board> createBoard(const vector<vector<Symbol>>& grid)
        {
            auto board = make_shared<Board>(m_logger);
            for (int row = 0; row < 3; ++row)
            {
                for (int col = 0; col < 3; ++col)
                {
                    if (grid[row][col] != Symbol::None) {
                        board->set_position(models::Position({row, col}, grid[row][col]));
                    }
                }
            }
            return board;
        }

        // Helper to create a game state
        shared_ptr<GameState> createGameState(shared_ptr<Board> board, const_player_ptr currentPlayer, Symbol lastPlaced = Symbol::None)
        {
            return make_shared<GameState>(nullptr, currentPlayer, board, lastPlaced);
        }

        // Helper to create a heuristic rollout strategy
        shared_ptr<HeuristicRolloutStrategy> createStrategy(shared_ptr<GameState> gameState)
        {
            return make_shared<HeuristicRolloutStrategy>(*gameState, m_logger);
        }

        // Helper to create action list from available positions
        vector<action_ptr> createActions(shared_ptr<GameState> gameState, shared_ptr<factories::TicTacToeFactory> factory)
        {
            vector<action_ptr> actions;
            auto openPositions = gameState->get_open_positions();
            auto node = factory->CreateNode("test");
            auto nodeBase = std::static_pointer_cast<monte_carlo::models::NodeBase<GameState, models::Position>>(node);

            for (const auto& pos : openPositions)
            {
                auto action = factory->CreateAction(nodeBase, *pos);
                actions.push_back(action);
            }
            return actions;
        }

        shared_ptr<sophia::logging::ILogger> m_logger;
        const_player_ptr m_playerX;
        const_player_ptr m_playerO;
    };

    TEST_F(HeuristicRolloutStrategyFixture, select_action_with_single_available_action)
    {
        // Arrange
        // Board state:
        //    1   2   3 
        // A  X | O | X 
        //   ---+---+---
        // B  O | X | O 
        //   ---+---+---
        // C  X | O |   
        auto board = createBoard({
            {X, O, X},
            {O, X, O},
            {X, O, _}
        });
        auto gameState = createGameState(board, m_playerX, O);
        auto strategy = createStrategy(gameState);
        auto factory = make_shared<factories::TicTacToeFactory>(nullptr, m_playerX, m_logger);
        auto actions = createActions(gameState, factory);

        // Act
        auto selectedAction = strategy->select_action(actions);

        // Assert
        ASSERT_NE(selectedAction, nullptr);
        EXPECT_EQ(selectedAction->name(), "C3");  // Position (2,2)
    }

    TEST_F(HeuristicRolloutStrategyFixture, select_action_with_empty_actions_list)
    {
        // Arrange
        // Board state:
        //    1   2   3 
        // A  X | O | X 
        //   ---+---+---
        // B  O | X | O 
        //   ---+---+---
        // C  X | O | X 
        auto board = createBoard({
            {X, O, X},
            {O, X, O},
            {X, O, X}
        });
        auto gameState = createGameState(board, m_playerX, X);
        auto strategy = createStrategy(gameState);
        vector<action_ptr> emptyActions;

        // Act
        auto selectedAction = strategy->select_action(emptyActions);

        // Assert
        EXPECT_EQ(selectedAction, nullptr);
    }

    TEST_F(HeuristicRolloutStrategyFixture, select_action_handles_multiple_corner_positions)
    {
        // Arrange - Only corner positions available
        // Board state:
        //    1   2   3 
        // A    | X |   
        //   ---+---+---
        // B  O | X | O 
        //   ---+---+---
        // C    | X |   
        const auto board = createBoard({
            {_, X, _},
            {O, X, O},
            {_, X, _}
        });
        auto gameState = createGameState(board, m_playerX, X);
        auto strategy = createStrategy(gameState);
        auto factory = make_shared<factories::TicTacToeFactory>(nullptr, m_playerX, m_logger);
        auto actions = createActions(gameState, factory);

        // Act
        auto selectedAction = strategy->select_action(actions);

        // Assert - Should select one of the available corner positions: A1, A3, C1, C3
        ASSERT_NE(selectedAction, nullptr);
        auto name = selectedAction->name();
        EXPECT_TRUE(name == "A1" || name == "A3" || name == "C1" || name == "C3");
    }

    // Test for blocking opponent winning moves
    TEST_F(HeuristicRolloutStrategyFixture, select_action_blocks_opponent_win)
    {
        // Arrange - Opponent (O) has two in a row, X needs to block
        // Board state:
        //    1   2   3 
        // A  X |   |
        //   ---+---+---
        // B    | X | O
        //   ---+---+---
        // C    |   | O
        auto board = createBoard({
            {X, _, _},
            {_, X, O},
            {_, _, O}
        });
        auto gameState = createGameState(board, m_playerX, O);
        auto strategy = createStrategy(gameState);
        auto factory = make_shared<factories::TicTacToeFactory>(nullptr, m_playerX, m_logger);
        auto actions = createActions(gameState, factory);

        // Act
        const auto selectedAction = strategy->select_action(actions);

        // Assert - Should block opponent by playing A3 (0,2)
        ASSERT_NE(selectedAction, nullptr);
        EXPECT_EQ(selectedAction->name(), "A3");
    }

    // Test for taking winning moves
    TEST_F(HeuristicRolloutStrategyFixture, select_action_takes_winning_opportunity)
    {
        // Arrange - X has two in a row and can win
        // Board state:
        //    1   2   3 
        // A  O |   |
        //   ---+---+---
        // B  O |   | X
        //   ---+---+---
        // C    |   | X
        auto board = createBoard({
            {O, _, _},
            {O, _, X},
            {_, _, X}
        });
        auto gameState = createGameState(board, m_playerX, X);
        auto strategy = createStrategy(gameState);
        auto factory = make_shared<factories::TicTacToeFactory>(nullptr, m_playerX, m_logger);
        auto actions = createActions(gameState, factory);

        // Act
        auto selectedAction = strategy->select_action(actions);

        // Assert - Should take winning move A3 (0,2)
        ASSERT_NE(selectedAction, nullptr);
        EXPECT_EQ(selectedAction->name(), "A3");
    }

    // Test constructor
    TEST_F(HeuristicRolloutStrategyFixture, constructor_initializes_correctly)
    {
        // Arrange
        // Board state:
        //    1   2   3 
        // A    |   |   
        //   ---+---+---
        // B    |   |   
        //   ---+---+---
        // C    |   |   
        auto board = createBoard({
            {_, _, _},
            {_, _, _},
            {_, _, _}
        });
        auto gameState = createGameState(board, m_playerX);

        // Act
        auto strategy = createStrategy(gameState);

        // Assert
        ASSERT_NE(strategy, nullptr);
        // Strategy should be properly initialized with game state and logger
    }

} // namespace sophia::monte_carlo::tic_tac_toe::model_tests