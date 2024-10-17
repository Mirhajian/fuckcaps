#include "unix_config_setup.hpp"
#include "yaml-cpp/node/parse.h"
#include "yaml_handler.hpp"

#include <iostream>

YAML::Node YamlHandler::config;

void YamlHandler::loadYamlConfigFile() {
    try {
        // std::cout << "Loading config file form: " << ConfigSetup::config_file_address << std::endl;

        config = YAML::LoadFile(ConfigSetup::config_file_address);

        if (!config.IsNull()) {
            // std::cout << config.size() << " items loaded successfully.\n";
        } else {
            std::cout << "Loading file failed or there are no items in the file.\n";
            return;
        }        
        
    } catch (const YAML::BadFile& e) {
        std::cerr << "YAML file error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << '\n';
    }
}
