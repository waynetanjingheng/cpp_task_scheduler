//
// Created by Wayne Tan on 19/8/24.
//

#ifndef PRIORITYTASK_HPP
#define PRIORITYTASK_HPP

#include<functional>

struct PriorityTask {
    std::function<void()> _task;
    int _priority; // Higher value means higher priority

    PriorityTask(std::function<void()> &&task, const int priority) : _task(std::move(task)), _priority(priority) {
    }

    bool operator<(const PriorityTask &other) const {
        return _priority < other._priority;
    }
};

#endif //PRIORITYTASK_HPP
