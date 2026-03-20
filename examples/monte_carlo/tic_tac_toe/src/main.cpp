#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <tic_tac_toe/models/human.h>
#include <tic_tac_toe/models/bot.h>
#include <tic_tac_toe/models/game.h>
#include <logging/log_dispatcher.h>
#include <memory>
#include <utility>
#include <iostream>

using sophia::monte_carlo::tic_tac_toe::factories::TicTacToeFactory;
using sophia::monte_carlo::tic_tac_toe::models::Game;
using sophia::monte_carlo::tic_tac_toe::models::Human;
using sophia::monte_carlo::tic_tac_toe::models::Bot;
using sophia::monte_carlo::tic_tac_toe::enums::Symbol;
using sophia::monte_carlo::tic_tac_toe::factories::RolloutStrategyType;
using sophia::logging::LogDispatcher;
using sophia::logging::LogLevel;
using std::make_shared;
using std::shared_ptr;


int main()
{
    const auto logger = make_shared<LogDispatcher>(LogLevel::Trace);
    logger->display("\033[2J");

    const shared_ptr<Game> game = make_shared<Game>(logger);
    game->print();

    // Define the callback for human player input
    auto get_human_move_input = []() -> std::string {
        std::string move_input;
        std::getline(std::cin, move_input);
        return move_input;
    };

    game->Assign<Human>(Symbol::X, get_human_move_input);
    game->Assign<Bot>(Symbol::O, 1.0, RolloutStrategyType::Heuristic);

    while(!game->game_over())
    {
        const auto current_player = game->active_player();

        const auto position = current_player->NextMove();

        if (position == nullptr)
        {
            break;
        }

        game->accept_move(*position);

        game->print();
    }

    logger->info("Game Over!");
    return 0;
}
