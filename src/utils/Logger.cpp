//
// Created by Wayne Tan on 18/8/24.
//

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "utils/Logger.hpp"

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    if (!_instance) {
        _instance = spdlog::stdout_color_mt("console");
        spdlog::set_level(spdlog::level::info);
    }
    return _instance;
}
