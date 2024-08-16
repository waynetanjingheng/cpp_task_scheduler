#include <iostream>

#include "TaskScheduler.hpp"
#include "../tests/MockTasks.hpp"

using Task = std::function<void()>;

int main() {
    TaskScheduler taskScheduler(4);

    int task1Id = 1;
    int task2Id = 2;
    int task3Id = 3;
    int task4Id = 4;

    Task task1 = [task1Id]()-> void { MockTasks::mockTaskWithRandomSleepDuration(task1Id); };
    Task task2 = [task2Id]()-> void { MockTasks::mockTaskWithComputation(task2Id); };
    Task task3 = [task3Id]()-> void { MockTasks::mockTaskWithContrivedError(task3Id); };
    Task task4 = [task4Id]()-> void { MockTasks::mockTaskQuick(task4Id); };

    taskScheduler.enqueueTask(task1Id, task1);
    taskScheduler.enqueueTask(task2Id, task2);
    taskScheduler.enqueueTask(task3Id, task3);
    taskScheduler.enqueueTask(task4Id, task4);

    taskScheduler.initialize();
    taskScheduler.start();


    return 1;
}
