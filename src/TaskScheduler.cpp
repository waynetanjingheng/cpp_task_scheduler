//
// Created by Wayne Tan on 14/8/24.
//

#include "TaskScheduler.hpp"
#include "utils/Logger.hpp"

const auto LOG = Logger::getLogger();

TaskScheduler::TaskScheduler(const size_t numWorkerThreads) : _numWorkerThreads(numWorkerThreads), _stop(false),
                                                              _tasksInExecutionCount(0), _initialized(false) {
}

TaskScheduler::~TaskScheduler() {
    _stop = true;

    _condition.notify_all();

    for (std::thread &worker: _workers) {
        worker.join();
    }
} // ensure graceful exit by joining all worker threads

void TaskScheduler::enqueueTask(const int taskId, std::function<void()> &task) { {
        std::lock_guard<std::mutex> taskQueueLock(_taskQueueMutex);
        _tasks.emplace(taskId, std::move(task));
        LOG->info("Task with id: {} enqueued to Task Queue.", taskId);
    }
    _condition.notify_one();
} // default implementation using basic FIFO

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
    // spawn threads in the pool and execute tasks in the queue
    for (size_t i = 0; i < _numWorkerThreads; i++) {
        _workers.emplace_back([this]()-> void { this->executeTasksFromQueue(); });
    }
}


size_t TaskScheduler::getTasksInExecutionCount() const {
    return _tasksInExecutionCount.load();
}

size_t TaskScheduler::getTasksInQueueCount() const {
    return _tasks.size();
}

// Default to a basic FIFO implementation
void TaskScheduler::executeTasksFromQueue() {
    while (true) {
        std::function<void()> task; {
            std::unique_lock<std::mutex> lock(_taskQueueMutex);
            _condition.wait(lock, [this]()-> bool { return _stop || !isTaskQueueEmpty(); });
            // thread should wake if `stop` is true (scheduler shutting down),
            // or there is a task to pop from the queue.
            if (_stop && isTaskQueueEmpty()) return;
            task = getNextTaskInQueue();
        }
        task();
    }
}


std::function<void()> TaskScheduler::getNextTaskInQueue() {
    auto [taskId, task] = std::move(_tasks.front());
    _tasks.pop();
    LOG->info("Task with id: {} popped from the Task Queue.", taskId);
    return task;
}

bool TaskScheduler::isTaskQueueEmpty() const {
    return _tasks.empty();
}
