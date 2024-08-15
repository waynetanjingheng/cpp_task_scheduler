cmake_minimum_required(VERSION 3.28)
project(task_scheduler)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
        include/TaskScheduler.hpp
        include/FIFOTaskScheduler.hpp
        src/main.cpp
        src/TaskScheduler.cpp
        src/FIFOTaskScheduler.cpp
        tests/MockTasks.hpp
        tests/MockTasks.cpp
)

add_executable(task_scheduler ${SOURCES}
)
