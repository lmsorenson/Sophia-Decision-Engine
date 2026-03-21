add_library(sophia_monte_carlo
        tree_search_algorithm.cpp)

target_link_libraries(sophia_monte_carlo PRIVATE sophia_logging)

add_subdirectory(factories)
add_subdirectory(models)
add_subdirectory(output)

target_include_directories(sophia_monte_carlo
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src)