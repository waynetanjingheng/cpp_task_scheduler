//
// Created by Wayne Tan on 14/8/24.
//

#include "TaskScheduler.hpp"

TaskScheduler::TaskScheduler(const size_t numWorkerThreads) : _stop(false), _tasksInExecutionCount(0) {
    // spawn threads in the pool and execute tasks in the queue
    for (size_t i = 0; i < numWorkerThreads; i++) {
        _workers.emplace_back([this]()-> void { this->executeTasksFromQueue(); });
    }
}

TaskScheduler::~TaskScheduler() {
    _stop = true;

    _condition.notify_all();

    for (std::thread &worker: _workers) {
        worker.join();
    }
} // ensure graceful exit by joining all worker threads

void TaskScheduler::enqueueTask(std::function<void()> &task) { {
        std::lock_guard<std::mutex> lock(_taskQueueMutex);
        _tasks.push(std::move(task));
    }
    _condition.notify_one();
} // default implementation using basic FIFO

size_t TaskScheduler::getTasksInExecutionCount() const {
    return _tasksInExecutionCount.load();
}

size_t TaskScheduler::getTasksInQueueCount() const {
    return _tasks.size();
}

std::function<void()> &TaskScheduler::getNextTaskInQueue() {
    std::function<void()> &&task = std::move(_tasks.front());
    _tasks.pop();
    return task;
}

bool TaskScheduler::isTaskQueueEmpty() const {
    return _tasks.empty();
}
