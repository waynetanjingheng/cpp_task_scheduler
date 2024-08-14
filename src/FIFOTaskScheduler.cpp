//
// Created by Wayne Tan on 14/8/24.
//

#include "FIFOTaskScheduler.hpp"

FIFOTaskScheduler::FIFOTaskScheduler(const size_t numWorkerThreads): TaskScheduler(numWorkerThreads) {
}

void FIFOTaskScheduler::executeTasksFromQueue() {
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
