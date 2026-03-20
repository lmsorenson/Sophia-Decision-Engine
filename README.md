# Sophia Decision Engine

[![CMake](https://github.com/lmsorenson/Sophia-Decision-Engine/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/lmsorenson/Sophia-Decision-Engine/actions/workflows/cmake-multi-platform.yml)
[![Documentation](https://github.com/lmsorenson/Sophia-Decision-Engine/actions/workflows/doxygen.yml/badge.svg)](https://github.com/lmsorenson/Sophia-Decision-Engine/actions/workflows/doxygen.yml)

**Sophia (σοφία)** means "Wisdom" - A high-performance C++ engine for intelligent decision-making through advanced tree search algorithms.

## Overview

Sophia Decision Engine is a high-performance C++ framework that provides the computational core for intelligent decision-making systems. Built around advanced tree search algorithms like Monte Carlo Tree Search (MCTS), it serves as the engine that powers AI agents, game-playing systems, and optimization applications.

## Features

- **Decision Engine Core**: Monte Carlo Tree Search (MCTS) as the computational engine for optimal decisions
- **Extensible Framework**: Plugin architecture supporting custom games, rollout strategies, and evaluation functions
- **High-Performance Templates**: Compile-time polymorphism with C++23 optimizations
- **Tree Search Foundation**: Extensible base for various decision-making algorithms
- **Comprehensive Testing**: Full unit test coverage ensuring reliability
- **Cross-Platform**: CMake-based build system supporting multiple compilers and platforms

## Requirements

- **C++ Compiler**: GCC 11+, Clang 14+, or MSVC 2022+ (C++23 support required)
- **CMake**: Version 3.29 or higher
- **Build System**: Ninja, Make, or Visual Studio (CMake generators)

## Installation

### Build from Source

```bash
# Clone the repository
git clone https://github.com/lmsorenson/Sophia-Decision-Engine.git
cd Sophia-Decision-Engine

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build . --config Release

# Install (optional)
cmake --install . --prefix /path/to/install
```

### Using as a CMake Subproject

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(path/to/Sophia-Decision-Engine)
target_link_libraries(your_target PRIVATE Sophia::DecisionEngine)
```

## Quick Start

### Basic Monte Carlo Tree Search Usage

```cpp
#include <monte_carlo/tree_search_algorithm.h>
#include <memory>

// Create your game state (implementing Node interface)
auto rootNode = std::make_shared<YourGameState>();

// Run MCTS for 1000 iterations
auto bestAction = sophia::monte_carlo::MonteCarloTreeSearch::run(rootNode, 1000);

// Execute the best action
bestAction->Execute();
```

### Tic-Tac-Toe Example

```cpp
#include <tic_tac_toe/factories/tic_tac_toe_factory.h>
#include <tic_tac_toe/models/game.h>
#include <memory>

int main() {
    // Create a new Tic-Tac-Toe game
    auto game = std::make_shared<sophia::monte_carlo::tic_tac_toe::models::Game>();

    // Add human and AI players
    game->Assign<sophia::monte_carlo::tic_tac_toe::models::Human>(
        sophia::monte_carlo::tic_tac_toe::enums::Symbol::X
    );

    game->Assign<sophia::monte_carlo::tic_tac_toe::models::Bot>(
        sophia::monte_carlo::tic_tac_toe::enums::Symbol::O, 0.9  // 90% exploration
    );

    // Play the game
    while (!game->game_over()) {
        auto currentPlayer = game->active_player();
        auto move = currentPlayer->NextMove();

        if (move) {
            game->accept_move(*move);
            game->print();
        }
    }

    return 0;
}
```

## Architecture

### Core Components

- **`Node`**: Represents game states with MCTS statistics
- **`Action`**: Represents moves/transitions between states
- **`RolloutStrategy`**: Defines how to evaluate leaf nodes
- **`MonteCarloTreeSearch`**: Main algorithm implementation

### Key Design Patterns

- **Template Method**: Node and Action classes define interfaces for customization
- **Strategy Pattern**: Pluggable rollout and selection strategies
- **Factory Pattern**: Game-specific object creation
- **Observer Pattern**: Event-driven game state updates

## Examples

The `examples/` directory contains complete implementations:

- **Tic-Tac-Toe**: Full game with human vs AI gameplay
- More examples coming soon...

Build and run examples:

```bash
cd build
cmake --build . --target tic_tac_toe_example
./examples/monte_carlo/tic_tac_toe/tic_tac_toe_example
```

## Testing

Run the test suite:

```bash
cd build
ctest --output-on-failure
```

Or build and run specific tests:

```bash
cmake --build . --target tests
./tests/monte_carlo_tests
```

## Documentation

- **API Documentation**: Generated with Doxygen
- **Build Instructions**: See above
- **Architecture Guide**: Coming soon

Generate documentation:

```bash
cd build
cmake --build . --target docs
# Open docs/html/index.html
```

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Setup

```bash
# Clone and setup
git clone https://github.com/lmsorenson/Sophia-Decision-Engine.git
cd Sophia-Decision-Engine

# Create build directory with development config
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON

# Run tests and linting
cmake --build . --target test
cmake --build . --target lint
```

### Code Style

- Use C++23 features where beneficial
- Follow the existing code style (braces, naming, etc.)
- Add unit tests for new functionality
- Update documentation for API changes

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Roadmap

- [ ] Additional rollout strategies (Neural network evaluation)
- [ ] Parallel MCTS implementation
- [ ] More game examples (Chess, Go, Connect Four)
- [ ] Optimization algorithms
- [ ] Python bindings
- [ ] Performance benchmarks

## Acknowledgments

- Inspired by modern MCTS implementations in game AI
- Built with modern C++ best practices
- Thanks to the C++ community for excellent tools and libraries

---

*"Wisdom is the right use of knowledge. To know is not to be wise. Many men know a great deal, and are all the greater fools for it. There is no fool so great a fool as a knowing fool. But to know how to use knowledge is to have wisdom."*
— Charles Spurgeon
