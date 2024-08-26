//
// Created by Wayne Tan on 25/8/24.
//

#ifndef USEROPTIONS_HPP
#define USEROPTIONS_HPP

class UserOptions {
public:
    static void displayOptionsAndAcceptInput();

    static const int getType();

    static const int getNumWorkerThreads();

    static const int getNumTasks();

private:
    static int type;
    static int numWorkerThreads;
    static int numTasks;

    static void setType(int type);

    static void setNumWorkerThreads(int numWorkerThreads);

    static void setNumTasks(int numTasks);
};


#endif //USEROPTIONS_HPP
