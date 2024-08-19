//
// Created by Wayne Tan on 15/8/24.
//

#ifndef MOCKTASKS_HPP
#define MOCKTASKS_HPP

namespace MockTasks {
    void mockTaskWithRandomSleepDuration(int taskId);

    void mockTaskWithComputation(int taskId);

    void mockTaskWithContrivedError(int taskId);

    void mockTaskQuick(int taskId);
}

#endif //MOCKTASKS_HPP
