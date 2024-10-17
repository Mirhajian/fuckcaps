#include "macos/macos_virtual_keycodes.hpp"
#include "macos_yaml_handler.hpp"
#include "unix_config_setup.hpp"
#include "yaml-cpp/emittermanip.h"
#include "yaml_handler.hpp"

#include <chrono>
#include <thread>

int UTILS::ACTION;
int UTILS::ALPHA;
int UTILS::RECORD;
int UTILS::DOWN;
int UTILS::LEFT;
int UTILS::RIGHT;
int UTILS::UP;

YAML::Node UTILS::ToggleKeys;
YAML::Node UTILS::ArrowKeys;

std::optional<int> UTILS::ACTION_OPT;
std::optional<int> UTILS::ALPHA_OPT;
std::optional<int> UTILS::RECORD_OPT;
std::optional<int> UTILS::LEFT_OPT;
std::optional<int> UTILS::DOWN_OPT;
std::optional<int> UTILS::UP_OPT;
std::optional<int> UTILS::RIGHT_OPT;

void UTILS::initialize() {
    ToggleKeys = YamlHandler::config["config"]["Toggle Keys"];
    ArrowKeys = YamlHandler::config["config"]["Arrow Keys"];

    // initialize key codes
    ACTION_OPT = KeyCodes::getKeyCode(ToggleKeys["Toggle Action Mode"].as<std::string>());
    ALPHA_OPT = KeyCodes::getKeyCode(ToggleKeys["Toggle Alpha Mode"].as<std::string>());
    RECORD_OPT = KeyCodes::getKeyCode(ToggleKeys["Toggle Record Mode"].as<std::string>());
    LEFT_OPT = KeyCodes::getKeyCode(ArrowKeys["Left"].as<std::string>());
    DOWN_OPT = KeyCodes::getKeyCode(ArrowKeys["Down"].as<std::string>());
    UP_OPT = KeyCodes::getKeyCode(ArrowKeys["Up"].as<std::string>());
    RIGHT_OPT = KeyCodes::getKeyCode(ArrowKeys["Right"].as<std::string>());

    // set the values of the static int variables
    ACTION = ACTION_OPT.has_value() ? ACTION_OPT.value() : -1;
    ALPHA = ALPHA_OPT.has_value() ? ALPHA_OPT.value() : -1;
    RECORD = RECORD_OPT.has_value() ? RECORD_OPT.value() : -1;
    DOWN = DOWN_OPT.has_value() ? DOWN_OPT.value() : -1;
    LEFT = LEFT_OPT.has_value() ? LEFT_OPT.value() : -1;
    RIGHT = RIGHT_OPT.has_value() ? RIGHT_OPT.value() : -1;
    UP = UP_OPT.has_value() ? UP_OPT.value() : -1;

    if (ACTION == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Toggle Action Mode'." << std::endl;
    } else if (ALPHA == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Toggle Alpha Mode'." << std::endl;
    } else if (RECORD == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Toggle Record Mode'." << std::endl;
    } else if (LEFT == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Left Arrow Key'." << std::endl;
    } else if (DOWN == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Down Arrow Key'." << std::endl;
    } else if (UP == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Up Arrow Key'." << std::endl;
    } else if (RIGHT == -1) {
        std::cerr << "NOT A VALID KEY-CODE FOR 'Right Arrow Key'." << std::endl;
    }

    std::set<std::string> valueSet;
    bool hasDuplicate = false;

    for (const auto& key : ArrowKeys) {
        std::string value = key.second.as<std::string>();
        if (valueSet.find(value) != valueSet.end()) {
            hasDuplicate = true;
            break;
        }
        valueSet.insert(value);
    }

    if (hasDuplicate) {
        std::cerr << "\nWARNING:" 
                  << "\nONE OR MORE VALUES OF THE ARROW KEYS ARE THE SAME," 
                  << "\nCONSIDER CHOOSING UNIQUE KEYS THIS. THE PROGRAM MAY NOT BEHAVE IN NORMAL WAY,"
                  << "\nCONSIDER FIXING THE CONFIGURATION." << std::endl;
    }
}

void UTILS::updateYamlFile(const std::string& section, const std::string& key, const std::string& value) {

    YAML::Node config = YamlHandler::config;

    if (!config["config"][section]) {
        std::cerr << "Section '" << section << "' not found in the configuration." << std::endl;
        return;
    }

    if (!config["config"][section][key]) {
        std::cerr << "Key '" << key << "' not found in section '" << section << "'." << std::endl; 
        return;
    }

    config["config"][section][key] = value;

    std::ofstream fout(ConfigSetup::config_file_address);
    // std::ofstream fout(YamlHandler::config_file_address);
    if (fout.is_open()) {
        fout << "---\n";
        fout << config;
        // fout << "...";
        fout.close();
        // std::cout << "Updated key '" << key << "' in section '" << section << "' with value '" << value << "'." << std::endl;
    } else {
        // std::cerr << "Unable to open the configuration file for writing." << std::endl;
    }
}
