//
// Created by Wayne Tan on 19/8/24.
//

#ifndef TASK_HPP
#define TASK_HPP

#include<functional>

// This struct defines the base struct of all Tasks in the program.
struct Task {
    std::function<void()> task;
    int taskId;

    Task(std::function<void()> task, const int taskId) : task(std::move(task)), taskId(taskId) {
    }

    virtual ~Task() = default;

    void execute() const {
        if (!task) {
            throw std::invalid_argument("Task function cannot be null!");
        }
        task();
    }
};

#endif //TASK_HPP
