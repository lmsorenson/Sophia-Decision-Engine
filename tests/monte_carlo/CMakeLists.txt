include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(sophia_monte_carlo_tests)
target_link_libraries(sophia_monte_carlo_tests
        gtest gtest_main
        gmock gmock_main
        sophia_monte_carlo
        sophia_monte_carlo_mocks
        sophia_monte_carlo_examples_tic_tac_toe)
target_include_directories(sophia_monte_carlo_tests
        PUBLIC ../../../include
        PUBLIC ../../../examples/monte_carlo/tic_tac_toe/include)
gtest_discover_tests(sophia_monte_carlo_tests)

add_subdirectory(mocks)
add_subdirectory(tree_search_algorithm_tests)
add_subdirectory(model_tests)

# Add tic-tac-toe tests from examples directory
target_sources(sophia_monte_carlo_tests
        PUBLIC ${CMAKE_SOURCE_DIR}/examples/monte_carlo/tic_tac_toe/tests/simulation_tests.cpp
        PUBLIC ${CMAKE_SOURCE_DIR}/examples/monte_carlo/tic_tac_toe/tests/state_tests.cpp
        PUBLIC ${CMAKE_SOURCE_DIR}/examples/monte_carlo/tic_tac_toe/tests/heuristic_rollout_strategy_tests.cpp
        PUBLIC ${CMAKE_SOURCE_DIR}/examples/monte_carlo/tic_tac_toe/tests/board_tests.cpp)