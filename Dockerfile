# STAGE 1: BUILD

FROM alpine:latest AS builder

# Install dependencies
RUN apk update \
    && apk upgrade \
    && apk add --no-cache \
    cmake \
    make \
    clang \
    git

#ENV CXX=clang++

WORKDIR /app

COPY . .

# Create a build directory and run CMake to configure the project
RUN rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && cd .. \
    && cmake --build ./build --target task_scheduler -j 6

# STAGE 2: RUN APPLICATION
FROM alpine:latest

RUN apk add --no-cache \
    libstdc++

WORKDIR /app

COPY --from=builder /app/build/task_scheduler .
COPY --from=builder /app/config.txt .

CMD ["./task_scheduler"]
