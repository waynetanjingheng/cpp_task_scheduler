//
// Created by Wayne Tan on 15/8/24.
//

#ifndef MOCKTASKFUNCTION_HPP
#define MOCKTASKFUNCTION_HPP

namespace MockTaskFunction {
    void mockTaskWithRandomSleepDuration(int taskId);

    void mockTaskWithComputation(int taskId);

    void mockTaskWithContrivedError(int taskId);

    void mockTaskQuick(int taskId);
}

#endif //MOCKTASKFUNCTION_HPP
