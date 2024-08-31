#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP

#include <queue>
#include <thread>
#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "tasks/Task.hpp"

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads);

    virtual ~TaskScheduler();

    virtual void enqueueTask(std::shared_ptr<Task> &task);

    // TODO: look into removing this entirely. Previously used to ensure
    // that the scheduler instance is fully constructed before `start` is invoked.
    void initialize();

    virtual void start();

    // To prevent the scheduler's destructor from being invoked prematurely,
    // which will free the derived class' member variables causing the worker threads
    // to access deallocated memory.
    virtual void waitForAllTasksToComplete();

    size_t getTasksInExecutionCount() const;

    size_t getTasksInQueueCount() const;

protected:
    size_t _numWorkerThreads;
    std::vector<std::thread> _workers; // worker thread pool

    // We use shared_ptr to bypass the restriction whereby std::priority_queue.top() returns
    // a const ref to the top element. If a unique_ptr is used, it is very difficult to
    // move the top pointer out of the pq (copy is not allowed for unique_ptr).
    // Even though std::queue is unaffected, we aim for consistency.
    std::queue<std::shared_ptr<Task> > _tasks;

    std::mutex _taskQueueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop; // flag to stop all worker threads
    std::atomic<size_t> _tasksInExecutionCount;
    std::atomic<bool> _initialized;
    std::mutex _initializationMutex;
    std::condition_variable _initializationCondition;

    virtual void executeTasksFromQueue();

    // Instead of returning a ref to a shared_ptr, we leverage copy elision/move semantics.
    virtual std::shared_ptr<Task> getNextTaskInQueue();

    virtual bool isTaskQueueEmpty() const;
};


#endif
