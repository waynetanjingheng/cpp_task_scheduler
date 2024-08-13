#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP
#include <queue>
#include <thread>
#include <vector>

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads) : _stop(false), _tasksInExecutionCount(0) {
        // spawn threads in the pool and execute tasks in the queue
        for (size_t i = 0; i < _tasks.size(); i++) {
            _workers.emplace_back([this] { this->executeTasksFromQueue(); });
        }
    };

    virtual ~TaskScheduler(); // ensure graceful exit by terminating all worker threads

    void enqueueTask(const std::function<void()> &task);

    virtual void waitForAllTasksToComplete();

    size_t getTasksInExecutionCount() const {
        return _tasksInExecutionCount.load();
    }

    size_t getTasksInQueueCount() const {
        return _tasks.size();
    }

private:
    std::vector<std::thread> _workers; // worker thread pool
    std::queue<std::function<void()> > _tasks;
    std::mutex _taskQueueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop; // flag to stop all worker threads
    std::atomic<size_t> _tasksInExecutionCount;

    virtual void executeTasksFromQueue() = 0;

    bool isTaskQueueEmpty() const {
        return _tasks.empty();
    }

    std::function<void()> &getNextTaskInQueue() {
        std::function<void()> &task = _tasks.front();
        _tasks.pop();
        return task;
    }
};


#endif
