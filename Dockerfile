FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    git \
    && rm -rf /var/lib/apt/lists/*

ENV CXX=clang++

RUN clang++ --version

WORKDIR /app

COPY . .

# Create a build directory and run CMake to configure the project
RUN rm -rf build \
    && mkdir -p build \
    && ls -l \
    && cd build \
    && ls -l \
    && cmake .. \
    && cd ..

# Run CMake to configure the project and generate makefiles
RUN cmake --build ./build --target task_scheduler -j 6

## Build the project
#RUN make

CMD ["./build/task_scheduler"]
