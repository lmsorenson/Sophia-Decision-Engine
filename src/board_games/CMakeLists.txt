set(BOARD_GAMES_SOURCES
        models/coordinate.cpp
        observer/subject.cpp
)

add_library(sophia_board_games STATIC ${BOARD_GAMES_SOURCES})

target_include_directories(sophia_board_games PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(sophia_board_games PUBLIC sophia_logging)
