//
// Created by Wayne Tan on 26/8/24.
//

#include "factory/TaskFactory.hpp"
#include <tasks/PriorityTask.hpp>
#include "view/UserOptions.hpp"
#include "MockTaskFunction.hpp"

const std::vector<std::shared_ptr<Task> > TaskFactory::getAllTasks() {
    const int numTasks = UserOptions::getNumTasks();

    std::vector<std::shared_ptr<Task> > tasks;

    // TODO: move this elsewhere for a single source of truth
    const std::vector<std::function<void(int taskId)> > mockFunctions = {
        MockTaskFunction::mockTaskWithRandomSleepDuration, MockTaskFunction::mockTaskWithComputation,
        MockTaskFunction::mockTaskWithContrivedError, MockTaskFunction::mockTaskQuick
    };
    const size_t mockFunctionsLength = mockFunctions.size();

    for (int i = 1; i <= numTasks; ++i) {
        tasks.push_back(getTask(i, mockFunctions[(i - 1) % mockFunctionsLength]));
    }

    return tasks;
}

const std::shared_ptr<Task> TaskFactory::getTask(const int taskId, const std::function<void(int tId)> mockFunction) {
    const int type = UserOptions::getType();

    switch (type) {
        case 2:
            return std::make_shared<PriorityTask>([taskId, mockFunction]()-> void {
                mockFunction(taskId);
            }, taskId, taskId);
        case 1:
            return std::make_shared<Task>([taskId, mockFunction]()-> void {
                mockFunction(taskId);
            }, taskId);
        default:
            throw std::invalid_argument("Invalid type!");
    }
}
