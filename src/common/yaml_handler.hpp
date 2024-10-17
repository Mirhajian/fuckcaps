#pragma once

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

class YamlHandler {
public:
    static void loadYamlConfigFile();
    static YAML::Node config;
};
