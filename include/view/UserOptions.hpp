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

private:
    static int type;
    static int numWorkerThreads;

    static void setType(int type);

    static void setNumWorkerThreads(int numWorkerThreads);
};


#endif //USEROPTIONS_HPP
