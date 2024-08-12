cmake_minimum_required(VERSION 3.28)
project(task_scheduler)

set(CMAKE_CXX_STANDARD 17)

add_executable(task_scheduler main.cpp
        include/TaskScheduler.hpp)
