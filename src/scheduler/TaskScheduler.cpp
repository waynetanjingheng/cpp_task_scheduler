//
// Created by Wayne Tan on 14/8/24.
//

#include "scheduler/TaskScheduler.hpp"
#include "utils/Logger.hpp"
#include "tasks/Task.hpp"

const auto LOG = Logger::getLogger();

TaskScheduler::TaskScheduler(const size_t numWorkerThreads) : _numWorkerThreads(numWorkerThreads), _stop(false),
                                                              _tasksInExecutionCount(0), _initialized(false) {
}

TaskScheduler::~TaskScheduler() {
    // As a safeguard, we always ensure graceful exit by enforcing that the
    // worker threads are joined before the object finishes destructing.
    // This is to protect against instances where waitForAllTasksToComplete()
    // is not invoked.
    _stop = true;

    _condition.notify_all();

    for (std::thread &worker: _workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void TaskScheduler::enqueueTask(std::shared_ptr<Task> &task) {
    // Default implementation using basic FIFO.

    {
        std::lock_guard<std::mutex> taskQueueLock(_taskQueueMutex);
        int taskId = task->taskId;

        // Under the assumption that the caller no longer needs the source shared_ptr.
        // Bypasses unnecessary increment/decrement of the atomic ref count.
        _tasks.emplace(std::move(task));

        LOG->info("Task with id: {} enqueued to Task Queue.", taskId);
    }
    _condition.notify_one();
}

void TaskScheduler::initialize() { {
        std::lock_guard<std::mutex> lock(_initializationMutex);
        _initialized = true;
    }
    _initializationCondition.notify_all();
}

void TaskScheduler::start() { {
        std::unique_lock<std::mutex> lock(_initializationMutex);
        _initializationCondition.wait(lock, [this]()-> std::atomic_bool *{ return &_initialized; });
    }
    // Spawn threads in the pool and execute tasks in the queue.
    for (size_t i = 0; i < _numWorkerThreads; i++) {
        _workers.emplace_back([this]()-> void { this->executeTasksFromQueue(); });
    }
}

void TaskScheduler::waitForAllTasksToComplete() {
    _stop = true;

    _condition.notify_all();

    for (auto &worker: _workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}


size_t TaskScheduler::getTasksInExecutionCount() const {
    return _tasksInExecutionCount.load();
}

size_t TaskScheduler::getTasksInQueueCount() const {
    return _tasks.size();
}

void TaskScheduler::executeTasksFromQueue() {
    while (true) {
        LOG->info("Thread polling...");
        std::shared_ptr<Task> taskPtr; {
            std::unique_lock<std::mutex> lock(_taskQueueMutex);
            _condition.wait(lock, [this]()-> bool { return _stop || !isTaskQueueEmpty(); });

            // Thread should wake if `stop` is true (scheduler shutting down),
            // or there is a task to pop from the queue.

            // _stop is set to true early in waitForAllTasksToComplete() before the task queue is empty.
            // We want threads to only stop polling once both conditions are fulfilled.
            if (_stop && isTaskQueueEmpty()) {
                LOG->info("Thread has finished polling.");
                return;
            };
            taskPtr = getNextTaskInQueue();
            // ++_tasksInExecutionCount;
        }
        taskPtr->execute();
    }
}


std::shared_ptr<Task> TaskScheduler::getNextTaskInQueue() {
    auto task = std::move(_tasks.front());
    _tasks.pop();
    LOG->info("Task with id: {} popped from the Task Queue.", task->taskId);
    return task;
}

bool TaskScheduler::isTaskQueueEmpty() const {
    return _tasks.empty();
}
