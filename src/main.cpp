#include "scheduler/TaskScheduler.hpp"
#include "MockTaskFunction.hpp"
#include "utils/Logger.hpp"
#include "tasks/Task.hpp"

int main() {
    const auto LOG = Logger::getLogger();
    LOG->info("Starting Program...");

    TaskScheduler taskScheduler(4);

    int task1Id = 1;
    int task2Id = 2;
    int task3Id = 3;
    int task4Id = 4;

    Task task1([task1Id]()-> void { MockTaskFunction::mockTaskWithRandomSleepDuration(task1Id); }, task1Id);
    Task task2([task2Id]()-> void { MockTaskFunction::mockTaskWithComputation(task2Id); }, task2Id);
    Task task3([task3Id]()-> void { MockTaskFunction::mockTaskWithContrivedError(task3Id); }, task3Id);
    Task task4([task4Id]()-> void { MockTaskFunction::mockTaskQuick(task4Id); }, task4Id);

    taskScheduler.enqueueTask(task1);
    taskScheduler.enqueueTask(task2);
    taskScheduler.enqueueTask(task3);
    taskScheduler.enqueueTask(task4);

    taskScheduler.initialize();
    taskScheduler.start();


    return 1;
}
