#pragma once

#include <string>

class ConfigSetup {
public:
    static std::string config_file_address;
    static void setupConfig();
private:
    static std::string getConfigDirectory();
    static bool directoryExists(const std::string& path);
    static bool fileExists(const std::string& path);
    static void createDirectory(const std::string& path);
    static void createConfigFile(const std::string& filePath);
};
