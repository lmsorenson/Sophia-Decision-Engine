/**
@mainpage Sophia Decision Engine API Documentation

@brief High-performance C++ framework for intelligent decision-making through Monte Carlo Tree Search

@section intro Introduction
Welcome to the Sophia Decision Engine API documentation. This library provides efficient implementations
of Monte Carlo Tree Search (MCTS) and related algorithms for intelligent decision-making.
*/

## Quick Start

```cpp
#include <sophia/monte_carlo/tree_search_algorithm.h>
#include <memory>

// Create your game state (implement Node interface)
auto root = std::make_shared<YourGameState>();

// Run MCTS to find optimal decision
auto bestAction = sophia::monte_carlo::MonteCarloTreeSearch::run(root, 1000);

// Execute the decision
bestAction->execute();
```

## Core Components

| Component                                                                                     | Purpose |
|-----------------------------------------------------------------------------------------------|---------|
| [MonteCarloTreeSearch](classsophia_1_1monte__carlo_1_1_monte_carlo_tree_search.html)          | Main algorithm implementation |
| [Node](classsophia_1_1monte__carlo_1_1models_1_1_node.html)                                   | Game state representation |
| [Action](classsophia_1_1monte__carlo_1_1models_1_1_action.html)                               | State transition representation |
| [Rollout Strategy](classsophia_1_1monte__carlo_1_1models_1_1_rollout_strategy_interface.html) | Leaf node evaluation strategy |

## Architecture Overview

### Decision-Making Pipeline

1. **Selection**: Traverse tree using UCB formula to find best leaf
2. **Expansion**: Add new child nodes to promising leaves
3. **Rollout**: Simulate random playout to terminal state
4. **Backpropagation**: Update statistics up the tree

### Template-Based Design

The library uses C++ templates for maximum performance:

```cpp
// NodeBase provides MCTS statistics for any game state type
template<typename TState, typename TAction>
class NodeBase : public Node {
    // MCTS visit count, total reward, etc.
};
```

## Example: Tic-Tac-Toe Integration

```cpp
#include <sophia/monte_carlo/tic_tac_toe/models/state.h>
#include <sophia/monte_carlo/tic_tac_toe/models/move.h>

// Create game state
auto gameState = std::make_shared<sophia::monte_carlo::tic_tac_toe::models::State>(
    "Initial State",
    initialBoard,
    factory
);

// Find best move
auto mcts = MonteCarloTreeSearch();
auto bestMove = mcts.run(gameState, 1000);

// Apply the move
bestMove->execute();
```

## Key Classes

### Algorithm Classes
- **[MonteCarloTreeSearch](classsophia_1_1monte__carlo_1_1_monte_carlo_tree_search.html)**: Core MCTS implementation
- **[TreeFactoryBase](classsophia_1_1monte__carlo_1_1factories_1_1_tree_factory_base.html)**: Abstract factory for game-specific objects

### Model Classes
- **[Node](classsophia_1_1monte__carlo_1_1models_1_1_node.html)**: Base class for game states
- **[Action](classsophia_1_1monte__carlo_1_1models_1_1_action.html)**: Base class for state transitions
- **[RolloutStrategyInterface](classsophia_1_1monte__carlo_1_1models_1_1_rollout_strategy_interface.html)**: Strategy for leaf evaluation

### Tic-Tac-Toe Example
- **[State](classsophia_1_1monte__carlo_1_1tic__tac__toe_1_1models_1_1_state.html)**: Tic-tac-toe game state
- **[Move](classsophia_1_1monte__carlo_1_1tic__tac__toe_1_1models_1_1_move.html)**: Tic-tac-toe move action
- **[TicTacToeFactory](classsophia_1_1monte__carlo_1_1tic__tac__toe_1_1factories_1_1_tic_tac_toe_factory.html)**: Factory for tic-tac-toe objects

## Usage Patterns

### Basic MCTS Usage
```cpp
// 1. Implement your game state extending Node
class MyGameState : public sophia::monte_carlo::models::Node {
    // Implement required virtual methods
};

// 2. Create factory for your game
class MyFactory : public sophia::monte_carlo::factories::TreeFactoryBase<GameState, Action> {
    // Implement factory methods
};

// 3. Run MCTS
auto root = std::make_shared<MyGameState>(initialState, factory);
auto bestAction = MonteCarloTreeSearch::run(root, iterations);
```

### Custom Rollout Strategy
```cpp
class MyStrategy : public sophia::monte_carlo::models::RolloutStrategyInterface {
public:
    double evaluate(const std::shared_ptr<Node>& node) override {
        // Your custom evaluation logic
        return score;
    }
};
```

## Performance Considerations

- **Iterations**: Higher iteration counts improve decision quality but increase computation time
- **Template Instantiation**: Compile-time optimization through templates
- **Memory Management**: Shared pointers ensure efficient memory usage
- **Thread Safety**: Single-threaded design (MCTS can be parallelized at higher level)

## Integration Guide

### CMake Integration
```cmake
find_package(SophiaDecisionEngine REQUIRED)
target_link_libraries(your_target Sophia::DecisionEngine)
```

### Header Usage
```cpp
// Core functionality
#include <sophia/monte_carlo/tree_search_algorithm.h>

// Model interfaces
#include <sophia/monte_carlo/models/node.h>
#include <sophia/monte_carlo/models/action.h>

// Factory interfaces
#include <sophia/monte_carlo/factories/tree_factory_interface.h>
```

## API Reference

- **[Namespaces](namespaces.html)**: Complete namespace overview
- **[Classes](classes.html)**: All classes with inheritance diagrams
- **[Files](files.html)**: Source file documentation

## See Also

- [GitHub Repository](https://github.com/lmsorenson/Sophia-Decision-Engine) - Source code and examples
- [Getting Started Guide](https://github.com/lmsorenson/Sophia-Decision-Engine/blob/master/README.md) - Project overview and installation

---

*"Wisdom is the right use of knowledge. To know is not to be wise. Many men know a great deal, and are all the greater fools for it."*
— Charles Spurgeon