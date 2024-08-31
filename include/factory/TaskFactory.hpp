//
// Created by Wayne Tan on 26/8/24.
//

#ifndef TASKFACTORY_HPP
#define TASKFACTORY_HPP

#include "tasks/Task.hpp"
#include <memory>

class TaskFactory {
public:
    static const std::vector<std::shared_ptr<Task>> getAllTasks();

private:
    static const std::shared_ptr<Task> getTask(int taskId, std::function<void(int tId)> mockFunction);
};

#endif //TASKFACTORY_HPP
