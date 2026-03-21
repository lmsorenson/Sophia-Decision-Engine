add_library(sophia_simulation STATIC)

add_subdirectory(interfaces)
add_subdirectory(models)

target_include_directories(sophia_simulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(sophia_simulation PUBLIC sophia_logging sophia_board_games)
