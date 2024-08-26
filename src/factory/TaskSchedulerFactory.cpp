//
// Created by Wayne Tan on 24/8/24.
//

#include "factory/TaskSchedulerFactory.hpp"
#include "scheduler/PriorityTaskScheduler.hpp"
#include "view/UserOptions.hpp"

const std::unique_ptr<TaskScheduler> TaskSchedulerFactory::getScheduler() {
    const int type = UserOptions::getType();
    const int numWorkerThreads = UserOptions::getNumWorkerThreads();

    switch (type) {
        case 1:
            return std::make_unique<TaskScheduler>(numWorkerThreads);
        case 2:
            return std::make_unique<PriorityTaskScheduler>(numWorkerThreads);
        default:
            throw std::invalid_argument("Invalid type!");
    }
}
