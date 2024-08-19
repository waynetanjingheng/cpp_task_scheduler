//
// Created by Wayne Tan on 19/8/24.
//

#ifndef TASK_HPP
#define TASK_HPP

#include<functional>

// This struct defines the base struct of all Tasks in the program.
struct Task {
    std::function<void()> _task;
    const int _taskId;

    Task(std::function<void()> &&task, const int taskId) : _task(std::move(task)), _taskId(taskId) {
    };

    void execute() const {
        _task();
    }
};

#endif //TASK_HPP
