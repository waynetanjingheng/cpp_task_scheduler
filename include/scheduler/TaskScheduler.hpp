#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP

#include <queue>
#include <thread>
#include <vector>
#include "tasks/Task.hpp"

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads);

    virtual ~TaskScheduler();

    virtual void enqueueTask(Task &task);

    void initialize();

    void start();

    // virtual void waitForAllTasksToComplete();

    size_t getTasksInExecutionCount() const;

    size_t getTasksInQueueCount() const;

protected:
    size_t _numWorkerThreads;
    std::vector<std::thread> _workers; // worker thread pool
    std::queue<Task> _tasks;
    std::mutex _taskQueueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop; // flag to stop all worker threads
    std::atomic<size_t> _tasksInExecutionCount;
    std::atomic_bool _initialized;
    std::mutex _initializationMutex;
    std::condition_variable _initializationCondition;

    virtual void executeTasksFromQueue();

    virtual Task &&getNextTaskInQueue();

    bool isTaskQueueEmpty() const;
};


#endif
