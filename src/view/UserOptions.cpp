//
// Created by Wayne Tan on 25/8/24.
//

#include<iostream>

#include "view/UserOptions.hpp"

int UserOptions::type = 0;
int UserOptions::numWorkerThreads = 0;

const int UserOptions::getType() {
    return type;
}

const int UserOptions::getNumWorkerThreads() {
    return numWorkerThreads;
}

void UserOptions::setType(const int type) {
    UserOptions::type = type;
}

void UserOptions::setNumWorkerThreads(const int numWorkerThreads) {
    UserOptions::numWorkerThreads = numWorkerThreads;
}

void UserOptions::displayOptionsAndAcceptInput() {
    std::cout << "Welcome! Please select a scheduling algorithm:" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "0: FIFO" << std::endl;
    std::cout << "1: Priority" << std::endl;
    std::cout << "=====================" << "\n" << std::endl;

    int type, numWorkerThreads;

    std::cin >> type;
    setType(type);

    std::cout << "Please input the number of worker threads in the scheduler:" << "\n" << std::endl;

    std::cin >> numWorkerThreads;
    setNumWorkerThreads(numWorkerThreads);

    std::cout << "Awesome! Initializing the scheduler..." << "\n" << std::endl;
}
