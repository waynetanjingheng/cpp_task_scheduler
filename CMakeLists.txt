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

add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/include)

set(SOURCES
        src/main.cpp
        src/scheduler/TaskScheduler.cpp
        tests/MockTaskFunction.cpp
        src/utils/Logger.cpp
        src/scheduler/PriorityTaskScheduler.cpp
        src/factory/TaskSchedulerFactory.cpp
        src/view/UserOptions.cpp
        src/factory/TaskFactory.cpp
        src/utils/FileReader.cpp
)

add_executable(task_scheduler ${SOURCES}
)

target_link_libraries(task_scheduler PRIVATE spdlog::spdlog)
