//
// Created by Wayne Tan on 20/8/24.
//

#ifndef PRIORITYTASKSCHEDULER_HPP
#define PRIORITYTASKSCHEDULER_HPP
#include "TaskScheduler.hpp"
#include "tasks/PriorityTask.hpp"

class PriorityTaskScheduler final : public TaskScheduler {
public:
    explicit PriorityTaskScheduler(size_t numWorkerThreads);

    ~PriorityTaskScheduler() override = default;

    void enqueueTask(std::shared_ptr<Task> &task) override;

private:
    struct TaskComparator {
        bool operator()(const std::shared_ptr<Task> &lhs, const std::shared_ptr<Task> &rhs) const {
            // Attempt to downcast the Task pointers to PriorityTask pointers.
            const auto lhsPriorityTask = dynamic_cast<PriorityTask *>(lhs.get());
            const auto rhsPriorityTask = dynamic_cast<PriorityTask *>(rhs.get());

            // Compare based on _priority if both are PriorityTask, otherwise simply return false.
            if (lhsPriorityTask && rhsPriorityTask) {
                return lhsPriorityTask->priority < rhsPriorityTask->priority;
            }
            return false;
        }
    };

    // We explicity rename the task queue here to avoid name hiding.
    std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task> >, TaskComparator> _priorityTasks;

    std::shared_ptr<Task> getNextTaskInQueue() override;

    bool isTaskQueueEmpty() const override;
};

#endif //PRIORITYTASKSCHEDULER_HPP
