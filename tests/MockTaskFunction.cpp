//
// Created by Wayne Tan on 15/8/24.
//

#include "MockTaskFunction.hpp"

#include <chrono>
#include <thread>
#include <mutex>
#include <random>
#include "utils/Logger.hpp"

const auto LOG = Logger::getLogger();

namespace MockTaskFunction {
    void mockTaskWithRandomSleepDuration(const int taskId) {
        std::random_device rd; // source for seeding
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);
        const int sleepDuration = dist(gen);
        LOG->info("Sleeping Task: {}  started, will take {} seconds.", taskId, sleepDuration);

        std::this_thread::sleep_for(std::chrono::seconds(sleepDuration));
        LOG->info("Sleeping Task: {} completed. Bye!", taskId);
    }

    void mockTaskWithComputation(const int taskId) { {
            LOG->info("Computation Task: {} started some intense computation.", taskId);
        }
        uint32_t sum = 0;
        const int bound = static_cast<int>(std::pow(10, 9));
        for (int i = 0; i < bound; i++) {
            sum += i;
        }
        LOG->info("Computation Task: {} completed computation with result: {}", taskId, sum);
    }

    void mockTaskWithContrivedError(const int taskId) {
        LOG->info("Potentially erroneous Task: {} started, might encounter an error.", taskId);

        try {
            if (taskId % 2 == 0) {
                throw std::runtime_error("Contrived error in task " + std::to_string(taskId));
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } catch (const std::exception &e) {
            LOG->error("Potentially erroneous Task: {} encountered an error: {}", taskId, e.what());
            return;
        }
        LOG->info("Potentially erroneous Task: {} completed successfully. Yay!", taskId);
    }

    void mockTaskQuick(const int taskId) {
        LOG->info("Quick Task: {} started quick execution.", taskId);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOG->info("Quick Task: {} completed quick execution.", taskId);
    }
}
