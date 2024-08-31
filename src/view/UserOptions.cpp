//
// Created by Wayne Tan on 25/8/24.
//

#include<iostream>

#include "view/UserOptions.hpp"
#include "utils/FileReader.hpp"

int UserOptions::type = 0;
int UserOptions::numWorkerThreads = 0;
int UserOptions::numTasks = 0;

const int UserOptions::getType() {
    return type;
}

const int UserOptions::getNumWorkerThreads() {
    return numWorkerThreads;
}

const int UserOptions::getNumTasks() {
    return numTasks;
}

void UserOptions::setType(const int type) {
    UserOptions::type = type;
}

void UserOptions::setNumWorkerThreads(const int numWorkerThreads) {
    UserOptions::numWorkerThreads = numWorkerThreads;
}

void UserOptions::setNumTasks(const int numTasks) {
    UserOptions::numTasks = numTasks;
}


void UserOptions::displayOptionsAndAcceptInput() {
    const std::string NUM_SCHEDULING_ALGORITHMS_KEY = "NUM_SCHEDULING_ALGORITHMS";
    const int NUM_SCHEDULING_ALGORITHMS = FileReader::getConfigValue(NUM_SCHEDULING_ALGORITHMS_KEY);

    std::cout << "Welcome! Please select a scheduling algorithm:" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "1: FIFO" << std::endl;
    std::cout << "2: Priority" << std::endl;
    std::cout << "=====================" << "\n" << std::endl;

    int type, numWorkerThreads, numTasks;

    std::cin >> type;
    if (type < 1 || type > NUM_SCHEDULING_ALGORITHMS) throw std::invalid_argument("Unknown type!");
    setType(type);

    std::cout << "Please input the number of worker threads in the scheduler:" << "\n" << std::endl;

    std::cin >> numWorkerThreads;
    if (numWorkerThreads <= 0) throw std::invalid_argument("Cannot have <= 0 worker threads!");
    setNumWorkerThreads(numWorkerThreads);

    std::cout << "Please input the number of tasks you wish to schedule:" << "\n" << std::endl;

    std::cin >> numTasks;
    if (numTasks <= 0) throw std::invalid_argument("Cannot have <= 0 tasks!");
    setNumTasks(numTasks);

    std::cout << "Awesome! Initializing the scheduler..." << "\n" << std::endl;
}
