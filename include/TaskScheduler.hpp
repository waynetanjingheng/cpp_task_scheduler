#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP
#include <queue>
#include <thread>
#include <vector>

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads);

    virtual ~TaskScheduler();

    virtual void enqueueTask(std::function<void()> &task);

    // virtual void waitForAllTasksToComplete();

    size_t getTasksInExecutionCount() const;

    size_t getTasksInQueueCount() const;

protected:
    std::vector<std::thread> _workers; // worker thread pool
    std::queue<std::function<void()> > _tasks;
    std::mutex _taskQueueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop; // flag to stop all worker threads
    std::atomic<size_t> _tasksInExecutionCount;

    virtual void executeTasksFromQueue() = 0;

    virtual std::function<void()> getNextTaskInQueue();

    bool isTaskQueueEmpty() const;
};


#endif
