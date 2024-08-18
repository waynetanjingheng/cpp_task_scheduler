//
// Created by Wayne Tan on 18/8/24.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/spdlog.h>

class Logger {
public:
    static std::shared_ptr<spdlog::logger> getLogger();

private:
    Logger() = default;

    static inline std::shared_ptr<spdlog::logger> _instance;
};

#endif
