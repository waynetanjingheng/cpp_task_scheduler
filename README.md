# C++ Task Scheduler

## Overview

This is my simple implementation of a task scheduler that supports some of the commonly-used scheduling algorithms used
by operating systems.
It is a simple application that takes in as input the number of worker threads and the number of tasks to execute.

### Tasks

In this project, tasks are nothing but objects that contain a member variable lambda that when executed, runs the mock
function in the lambda. This simulates some job that can take up to a few seconds to finish.

Although you may input the number of tasks to execute, the type of mock function in each task is automatically assigned
based on (taskId % 4). Currently, there are 4 mock functions supported:

1. `void mockTaskWithRandomSleepDuration(int taskId)`: Simulates some non-deterministic sleep time
2. `void mockTaskWithComputation(int taskId)`: Performs some simple arithmetic up to the order of 10^9
3. `void mockTaskWithContrivedError(const int taskId)`: May throw std::runtime_error depending on the parity of the
   taskId
4. `void mockTaskQuick(const int taskId)`: A very simple task that completes almost immediately

### Currently supported Scheduling Algorithms

1. FIFO
2. Priority (based on taskId descending)

### Thread pool

The scheduler leverages the concept of a thread pool, which is essentially a collection of pre-instantiated, idle
threads that stand ready to perform tasks. This can promote efficiency since we do not face the overhead of repeatedly
creating and destroying threads for each single task.
Furthermore, the number of threads are fixed, giving greater control over system resource exhaustion and stability.

### Factory Design Pattern

Of course, the application does not know beforehand which scheduling algorithm you are going to choose. Thus, a factory
design pattern has been employed to allow for polymorphic behaviour, where the clients are only concerned with the
base `TaskScheduler` and `Task` types.

## Prerequisites

Before running this project, ensure you have the following installed:

- [Docker](https://docs.docker.com/get-docker/)

## Getting Started

### Cloning the Repository

First, clone the repository to your local machine:

```bash
git clone https://github.com/waynetanjingheng/cpp_task_scheduler.git
```

### Build the Docker Image

```
docker build -t task_scheduler .
```

### Run the Application

```
docker run -it task_scheduler
```

