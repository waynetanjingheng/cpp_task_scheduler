#include "scheduler/TaskScheduler.hpp"
#include "factory/TaskSchedulerFactory.hpp"
#include "factory/TaskFactory.hpp"
#include "tasks/PriorityTask.hpp"
#include "utils/Logger.hpp"
#include "tasks/Task.hpp"
#include "view/UserOptions.hpp"

int main() {
    const auto LOG = Logger::getLogger();
    LOG->info("Starting Program...");

    UserOptions::displayOptionsAndAcceptInput();

    const std::unique_ptr<TaskScheduler> taskScheduler = TaskSchedulerFactory::getScheduler();

    std::vector<std::shared_ptr<Task> > tasks = TaskFactory::getAllTasks();

    for (auto &task: tasks) {
        taskScheduler->enqueueTask(task);
    }

    taskScheduler->initialize();
    taskScheduler->start();
    taskScheduler->waitForAllTasksToComplete();


    return 1;
}
