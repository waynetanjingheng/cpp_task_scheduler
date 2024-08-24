//
// Created by Wayne Tan on 24/8/24.
//

#ifndef TASKSCHEDULERFACTORY_HPP
#define TASKSCHEDULERFACTORY_HPP

#include <memory>
#include "scheduler/TaskScheduler.hpp"

class TaskSchedulerFactory {
public:
    static const std::unique_ptr<TaskScheduler> getScheduler();
};

#endif //TASKSCHEDULERFACTORY_HPP
