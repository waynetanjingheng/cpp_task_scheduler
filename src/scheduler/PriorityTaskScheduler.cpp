//
// Created by Wayne Tan on 20/8/24.
//

#include "scheduler/PriorityTaskScheduler.hpp"
#include "utils/Logger.hpp"
#include <sstream>

const auto LOG = Logger::getLogger();

PriorityTaskScheduler::PriorityTaskScheduler(const size_t numWorkerThreads) : TaskScheduler(numWorkerThreads) {
}

void PriorityTaskScheduler::enqueueTask(std::shared_ptr<Task> &task) {
    // TODO: look into adding a method to get a ref to the underlying task queue (regardless of derived class).
    // This would then allow all derived classes to reuse the base method without needing to override it.

    {
        std::lock_guard<std::mutex> taskQueueLock(_taskQueueMutex);
        int taskId = task->taskId;
        _priorityTasks.emplace(std::move(task));
        LOG->info("Task with id: {} enqueued to Task Queue.", taskId);
    }
    _condition.notify_one();
}

std::shared_ptr<Task> PriorityTaskScheduler::getNextTaskInQueue() {
    const auto taskPtr = _priorityTasks.top();
    LOG->info("Task with id: {} popped from the Task Queue.", taskPtr->taskId);
    _priorityTasks.pop();
    return taskPtr;
}


bool PriorityTaskScheduler::isTaskQueueEmpty() const {
    // TODO: Likewise, implement a method to get a ref to the underlying task queue so that this need not be overriden.

    return _priorityTasks.empty();
}
