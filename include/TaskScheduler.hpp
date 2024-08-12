#ifndef TASKSCHEDULER_HPP
#define TASKSCHEDULER_HPP
#include <queue>
#include <thread>
#include <vector>

class TaskScheduler {
public:
    explicit TaskScheduler(size_t numWorkerThreads);

    ~TaskScheduler(); // ensure graceful exit by terminating all worker threads

    void enqueueTask(const std::function<void()> &task);

    void waitForAllTasksToComplete();

private:
    std::vector<std::thread> _workers; // worker thread pool
    std::queue<std::function<void()> > _tasks;
    std::mutex _queueMutex;
    std::condition_variable _condition;
    std::atomic<bool> _stop; // flag to stop all worker threads
    std::atomic<size_t> _activeTasks;

    void executeTasksFromQueue();
};


#endif
