#pragma once

#include "macos_virtual_keycodes.hpp"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml_handler.hpp"

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

class UTILS {
public:
    static void initialize();
    static int ACTION;
    static int ALPHA;
    static int RECORD;
    static int DOWN;
    static int LEFT;
    static int RIGHT;
    static int UP;

    static void updateYamlFile(const std::string& section, const std::string& key, const std::string& value);

private:
    static YAML::Node ToggleKeys;
    static YAML::Node ArrowKeys;
    static std::optional<int> ACTION_OPT;
    static std::optional<int> ALPHA_OPT;
    static std::optional<int> RECORD_OPT;
    static std::optional<int> LEFT_OPT;
    static std::optional<int> DOWN_OPT;
    static std::optional<int> UP_OPT;
    static std::optional<int> RIGHT_OPT;
};
