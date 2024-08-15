//
// Created by Wayne Tan on 15/8/24.
//

#include "MockTasks.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <random>


namespace MockTasks {
    void mockTaskWithRandomSleepDuration(const int taskId) {
        static std::mutex outputStreamMutex;
        std::random_device rd; // source for seeding
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);
        int sleepDuration = dist(gen); {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Sleeping Task " << taskId << " started, will take " << sleepDuration << " seconds." <<
                    std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(sleepDuration)); {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Sleeping Task " << taskId << " completed. Bye!" << std::endl;
        }
    }

    void mockTaskWithComputation(const int taskId) {
        static std::mutex outputStreamMutex; {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Compute Task " << taskId << " started some intense computation." << std::endl;
        }
        int sum = 0, i = 0, bound = static_cast<int>(std::pow(10, 9));
        for (; i < bound; i++) {
            sum += i;
        } {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Compute Task " << taskId << " completed computation with result: " << sum << std::endl;
        }
    }

    void mockTaskWithContrivedError(const int taskId) {
        static std::mutex outputStreamMutex; {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Potentially erroneous Task " << taskId << " started, might encounter an error." << std::endl;
        }

        try {
            if (taskId % 2 == 0) {
                throw std::runtime_error("Contrived error in task " + std::to_string(taskId));
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } catch (const std::exception &e) {
            {
                std::lock_guard<std::mutex> lock(outputStreamMutex);
                std::cout << "Potentially erroneous Task " << taskId << " encountered an error: " << e.what() <<
                        std::endl;
            }
            return;
        } {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Potentially erroneous Task " << taskId << " completed successfully. Yay!" << std::endl;
        }
    }

    void mockTaskQuick(const int taskId) {
        static std::mutex outputStreamMutex; {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Quick Task " << taskId << " started quick execution." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); {
            std::lock_guard<std::mutex> lock(outputStreamMutex);
            std::cout << "Quick Task " << taskId << " completed quick execution." << std::endl;
        }
    }
}
