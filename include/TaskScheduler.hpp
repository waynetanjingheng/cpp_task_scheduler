#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP
#include <queue>
#include <thread>
#include <vector>

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads) : _stop(false), _tasksInExecutionCount(0) {
        // spawn threads in the pool and execute tasks in the queue
        for (size_t i = 0; i < numWorkerThreads(); i++) {
            _workers.emplace_back([this]()-> void { this->executeTasksFromQueue(); });
        }
    };

    virtual ~TaskScheduler() {
        _stop = true;

        _condition.notify_all();

        for (std::thread &worker: _workers) {
            worker.join();
        }
    }; // ensure graceful exit by joining all worker threads


    virtual void enqueueTask(std::function<void()> &task) { {
            std::lock_guard<std::mutex> lock(_taskQueueMutex);
            _tasks.push(std::move(task));
        }
        _condition.notify_one();
    }; // default implementation using basic FIFO

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

    virtual std::function<void()> &getNextTaskInQueue() {
        std::function<void()> &task = _tasks.front();
        _tasks.pop();
        return task;
    }

    bool isTaskQueueEmpty() const {
        return _tasks.empty();
    }
};


#endif
