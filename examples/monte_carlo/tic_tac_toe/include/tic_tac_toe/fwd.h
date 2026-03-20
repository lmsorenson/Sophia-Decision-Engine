#ifndef SOPHIA_TIC_TAC_TOE_FWD_H
#define SOPHIA_TIC_TAC_TOE_FWD_H

namespace sophia::monte_carlo::tic_tac_toe::factories {
    enum class RolloutStrategyType {
        Random,
        Heuristic
    };
}

namespace sophia::monte_carlo::factories {
    template <typename GameStateType, typename ActionType> class TreeFactoryBase;
}

namespace sophia::monte_carlo::tic_tac_toe::models {
    class Board;
    class Bot;
    class Game;
    class GameState;
    class HeuristicRolloutStrategy;
    class Human;
    class Move;
    class Player;
    class Position;
    class State;
}

namespace sophia::monte_carlo::tic_tac_toe::observer {
    class Observer;
}

#endif // SOPHIA_TIC_TAC_TOE_FWD_H
