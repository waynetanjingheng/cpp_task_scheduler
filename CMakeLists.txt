cmake_minimum_required(VERSION 3.28)
project(task_scheduler)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.14.1
)

FetchContent_MakeAvailable(spdlog)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        src/main.cpp
        src/TaskScheduler.cpp
        tests/MockTasks.hpp
        tests/MockTasks.cpp
        src/utils/Logger.cpp
)

add_executable(task_scheduler ${SOURCES}
)

target_link_libraries(task_scheduler PRIVATE spdlog::spdlog)
