//
// Created by Wayne Tan on 26/8/24.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#include "utils/FileReader.hpp"


const int FileReader::getConfigValue(const std::string &configKey) {
    const std::filesystem::path ROOT_DIR = PROJECT_ROOT;
    const std::filesystem::path CONFIG_FILE_NAME = "config.txt";
    const std::filesystem::path CONFIG_FILE_PATH = ROOT_DIR / CONFIG_FILE_NAME;
    std::ifstream configFile(CONFIG_FILE_PATH);
    std::string line;

    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string currentKey;

        std::getline(iss, currentKey, '=');

        if (currentKey == configKey) {
            int value;
            iss >> value;
            return value;
        }
    }
    // Return a default value or handle the key not found case
    return -1;
}
