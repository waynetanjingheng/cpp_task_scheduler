#include "scheduler/TaskScheduler.hpp"
#include "factory/TaskSchedulerFactory.hpp"
#include "tasks/PriorityTask.hpp"
#include "MockTaskFunction.hpp"
#include "utils/Logger.hpp"
#include "tasks/Task.hpp"
#include "view/UserOptions.hpp"

int main() {
    const auto LOG = Logger::getLogger();
    LOG->info("Starting Program...");

    UserOptions::displayOptionsAndAcceptInput();

    const std::unique_ptr<TaskScheduler> taskScheduler = TaskSchedulerFactory::getScheduler();

    // TODO: refactor all these into a loop or something cleaner.

    int task1Id = 1;
    int task2Id = 2;
    int task3Id = 3;
    int task4Id = 4;

    // auto task1 = std::make_unique<Task>([task1Id]()-> void { MockTaskFunction::mockTaskWithRandomSleepDuration(task1Id); }, task1Id);
    // auto task2 = std::make_unique<Task>([task2Id]()-> void { MockTaskFunction::mockTaskWithComputation(task2Id); }, task2Id);
    // auto task3 = std::make_unique<Task>([task3Id]()-> void { MockTaskFunction::mockTaskWithContrivedError(task3Id); }, task3Id);
    // auto task4 = std::make_unique<Task>([task4Id]()-> void { MockTaskFunction::mockTaskQuick(task4Id); }, task4Id);

    std::shared_ptr<Task> task1 = std::make_shared<PriorityTask>([task1Id]()-> void {
        MockTaskFunction::mockTaskWithRandomSleepDuration(task1Id);
    }, task1Id, 1);
    std::shared_ptr<Task> task2 = std::make_shared<PriorityTask>([task2Id]()-> void {
        MockTaskFunction::mockTaskWithComputation(task2Id);
    }, task2Id, 2);
    std::shared_ptr<Task> task3 = std::make_shared<PriorityTask>([task3Id]()-> void {
        MockTaskFunction::mockTaskWithContrivedError(task3Id);
    }, task3Id, 3);
    std::shared_ptr<Task> task4 = std::make_shared<PriorityTask>([task4Id]()-> void {
        MockTaskFunction::mockTaskQuick(task4Id);
    }, task4Id, 4);

    taskScheduler->enqueueTask(task1);
    taskScheduler->enqueueTask(task2);
    taskScheduler->enqueueTask(task3);
    taskScheduler->enqueueTask(task4);

    taskScheduler->initialize();
    taskScheduler->start();
    taskScheduler->waitForAllTasksToComplete();


    return 1;
}
