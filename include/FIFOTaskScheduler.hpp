#ifndef FIFOTASKSCHEDULER_HPP
#define FIFOTASKSCHEDULER_HPP

#include "TaskScheduler.hpp"

class FIFOTaskScheduler : public TaskScheduler {
public:
    explicit FIFOTaskScheduler(size_t numWorkerThreads);

protected:
    void executeTasksFromQueue() override;
};


#endif
