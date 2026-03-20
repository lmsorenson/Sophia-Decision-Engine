#ifndef SOPHIA_TIC_TAC_TOE_COMMON_ALIASES_H
#define SOPHIA_TIC_TAC_TOE_COMMON_ALIASES_H

#include <memory>

#include <tic_tac_toe/fwd.h>

namespace sophia::monte_carlo::tic_tac_toe {
    // Aliases for shared pointers to game components
    using board_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Board>;
    using const_board_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Board>;

    using bot_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Bot>;
    using const_bot_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Bot>;

    using game_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Game>;
    using const_game_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Game>;
    using game_ref = std::weak_ptr<sophia::monte_carlo::tic_tac_toe::models::Game>;
    using const_game_ref = std::weak_ptr<const sophia::monte_carlo::tic_tac_toe::models::Game>;

    using game_state_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::GameState>;
    using const_game_state_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::GameState>;

    using heuristic_rollout_strategy_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy>;
    using const_heuristic_rollout_strategy_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::HeuristicRolloutStrategy>;

    using human_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Human>;
    using const_human_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Human>;

    using move_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Move>;
    using const_move_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Move>;

    using player_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Player>;
    using const_player_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Player>;

    using position_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::Position>;
    using const_position_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::Position>;

    using state_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::models::State>;
    using const_state_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::models::State>;

    using tic_tac_toe_tree_factory_base_ptr = std::shared_ptr<const sophia::monte_carlo::factories::TreeFactoryBase<sophia::monte_carlo::tic_tac_toe::models::GameState, sophia::monte_carlo::tic_tac_toe::models::Position>>;

    using observer_ptr = std::shared_ptr<sophia::monte_carlo::tic_tac_toe::observer::Observer>;
    using const_observer_ptr = std::shared_ptr<const sophia::monte_carlo::tic_tac_toe::observer::Observer>;
}

#endif // SOPHIA_TIC_TAC_TOE_COMMON_ALIASES_H
