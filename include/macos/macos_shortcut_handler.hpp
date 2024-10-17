#pragma once

#include <unordered_map>
#include <string>

class MacOSShortcutHandler {
public:
    static void initialize();
    static void handleShortcut(const std::string& key);
    static void saveShortcut(const std::string& sumKeyCodes);

private:
    static std::unordered_map<std::string, std::string> shortcuts;

    static void executeCommand(const std::string& command);
};
