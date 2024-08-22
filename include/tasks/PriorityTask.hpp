//
// Created by Wayne Tan on 19/8/24.
//

#ifndef PRIORITYTASK_HPP
#define PRIORITYTASK_HPP

#include "tasks/Task.hpp"
#include<functional>

struct PriorityTask : Task {
    int priority; // Higher value means higher priority

    PriorityTask(std::function<void()> &&task, const int taskId, const int priority) : Task(std::move(task), taskId),
        priority(priority) {
    }

    ~PriorityTask() override = default;

    bool operator<(const PriorityTask &other) const {
        return priority < other.priority;
    }
};

#endif //PRIORITYTASK_HPP
