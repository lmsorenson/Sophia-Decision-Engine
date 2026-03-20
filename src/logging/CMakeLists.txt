add_library(sophia_logging
        console_logger.cpp
        log_dispatcher.cpp
        file_logger.cpp
        dummy_logger.cpp)

target_include_directories(sophia_logging
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include)
