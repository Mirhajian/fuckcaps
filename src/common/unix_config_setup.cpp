#include "unix_config_setup.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/stat.h>
#include <unistd.h>

std::string ConfigSetup::config_file_address;

std::string ConfigSetup::getConfigDirectory() {
    const char* homeDir = std::getenv("HOME");
    if (homeDir == nullptr) {
        std::cerr << "Error: Could not find home directory!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string configDir = std::string(homeDir) + "/.config/fuckcaps/";

    return configDir;
}

bool ConfigSetup::directoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0; // if the path exists
}

bool ConfigSetup::fileExists(const std::string& path) {
    return access(path.c_str(), F_OK) != -1;
}

void ConfigSetup::createDirectory(const std::string& path) {
    if (mkdir(path.c_str(), 0777) != 0) {
        std::cerr << "Error: Could not create directory " << path << std::endl;
        exit(EXIT_FAILURE);
    }
}

#ifdef __APPLE__
void ConfigSetup::createConfigFile(const std::string& filePath) {
    std::ofstream configFile(filePath);
    if (configFile.is_open()) {
        configFile << "---\n"
                   << "config:\n"
                   << "  Arrow Keys:\n"
                   << "    Left: h\n"
                   << "    Right: l\n"
                   << "    Down: j\n"
                   << "    Up: k\n\n"
                   << "  Toggle Keys:\n"
                   << "    Toggle Action Mode: \"`\"\n"
                   << "    Toggle Alpha Mode: \".\"\n"
                   << "    Toggle Record Mode: \"ESCAPE\"\n\n"
                   << "  Shortcuts:\n"
                   << "    a: \"COMMAND+c\"\n"    // Copy
                   << "    b: \"COMMAND+v\"\n"    // Paste
                   << "    c: \"COMMAND+x\"\n"    // Cut
                   << "    d: \"COMMAND+z\"\n"    // Undo
                   << "    e: \"COMMAND+a\"\n"    // Select All
                   << "    f: \"COMMAND+f\"\n"    // Find
                   << "    g: \"COMMAND+s\"\n"    // Save
                   << "    h: \"COMMAND+n\"\n"    // New Window
                   << "    i: \"COMMAND+tab\"\n"   // Switch Applications
                   << "    j: \"COMMAND+OPTION+ESC\"\n" // Force Quit Applications
                   << "    k: \"COMMAND+SHIFT+3\"\n" // Taking ScreenShot
                   << "    l: ~\n"
                   << "    m: ~\n"
                   << "    n: ~\n"
                   << "    o: ~\n"
                   << "    p: ~\n"
                   << "    q: ~\n"
                   << "    r: ~\n"
                   << "    s: ~\n"
                   << "    t: ~\n"
                   << "    u: ~\n"
                   << "    v: ~\n"
                   << "    w: ~\n"
                   << "    x: ~\n"
                   << "    y: ~\n"
                   << "    z: ~\n"
                   << "    1: ~\n"
                   << "    2: ~\n"
                   << "    3: ~\n"
                   << "    4: ~\n"
                   << "    5: ~\n"
                   << "    6: ~\n"
                   << "    7: ~\n"
                   << "    8: ~\n"
                   << "    9: ~\n"
                   << "    0: ~\n"
                   << "    \"-\": ~\n"
                   << "    \"=\": ~\n"
                   << "    \"/\": ~\n"
                   << "    \"\\\\\": ~\n"
                   << "    \".\": ~\n"
                   << "    \",\": ~\n"
                   << "    \"[\": ~\n"
                   << "    \"]\": ~\n"
                   << "    \"`\": ~\n";
        configFile.close();
        // std::cout << "Configuration file created at: " << filePath << std::endl;
    } else {
        std::cerr << "Error: Could not create configuration file!" << std::endl;
        exit(EXIT_FAILURE);
    }
}
#elif __linux__
// still in development
void ConfigSetup::createConfigFile(const std::string& filePath) {}
#endif

void ConfigSetup::setupConfig() {
    std::string configDir = getConfigDirectory();
    
    if (!directoryExists(configDir)) {
        // std::cout << "Creating config directory: " << configDir << std::endl;
        createDirectory(configDir);
    }

    std::string configFilePath = configDir + "key_configs.yaml";
    ConfigSetup::config_file_address = configFilePath;
    // std::cout << configFilePath << std::endl;

    if (!fileExists(configFilePath)) {
        // std::cout << "Creating configuration file at: " << configFilePath << std::endl;
        createConfigFile(configFilePath);
    }
}
