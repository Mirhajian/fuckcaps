#include "macos_shortcut_handler.hpp"
#include "macos_virtual_keycodes.hpp"
#include "macos_yaml_handler.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <CoreGraphics/CGEvent.h>
#include <sstream>
#include <string>
#include <vector>
#include <optional>

std::unordered_map<std::string, std::string> MacOSShortcutHandler::shortcuts;

void MacOSShortcutHandler::initialize() {
    // Load the shortcut mappings from the YAML config file
    auto shortcutNode = YamlHandler::config["config"]["Shortcuts"];
    for (const auto& shortcut : shortcutNode) {
        std::string key = shortcut.first.as<std::string>();
        std::string command = shortcut.second.IsNull() ? "" : shortcut.second.as<std::string>();
        if (!command.empty()) {
            shortcuts[key] = command;
        }
    }
}

void MacOSShortcutHandler::handleShortcut(const std::string& key) {
    auto it = shortcuts.find(key);
    if (it != shortcuts.end()) {
        std::string command = it->second;
        if (!command.empty()) {
            executeCommand(command);
        }
    }
}

void MacOSShortcutHandler::executeCommand(const std::string& command) {
    CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    std::vector<CGEventRef> events;

    std::istringstream commandStream(command);
    std::string keyPart;
    CGEventFlags flags = 0;
    std::optional<int> keyCode;

    while (std::getline(commandStream, keyPart, '+')) {
        if (keyPart == "CONTROL") {
            flags |= kCGEventFlagMaskControl;
        } else if (keyPart == "COMMAND") {
            flags |= kCGEventFlagMaskCommand;
        } else if (keyPart == "OPTION") {
            flags |= kCGEventFlagMaskAlternate;
        } else if (keyPart == "SHIFT") {
            flags |= kCGEventFlagMaskShift;
        } else if (keyPart == "RETURN") {
            CGEventRef event = CGEventCreateKeyboardEvent(source, 36, true);
            CGEventSetFlags(event, flags);
            events.push_back(event);
        } else if (keyPart == "LA") {
            CGEventRef event = CGEventCreateKeyboardEvent(source, 123, true);
            CGEventSetFlags(event, flags);
            events.push_back(event);
        } else if (keyPart == "RA") {
            CGEventRef event = CGEventCreateKeyboardEvent(source, 124, true);
            CGEventSetFlags(event, flags);
            events.push_back(event);
        } else {
            // It's the actual key
            keyCode = KeyCodes::getKeyCode(keyPart);
            if (keyCode) {
                CGEventRef event = CGEventCreateKeyboardEvent(source, keyCode.value(), true); // Key down
                CGEventSetFlags(event, flags);
                events.push_back(event);
            }
        }
    }

    // post all events (key down)
    for (auto event : events) {
        CGEventPost(kCGHIDEventTap, event);
        CFRelease(event);
    }

    // create and post key up events for all keys
    for (auto event : events) {
        CGEventRef keyUpEvent = CGEventCreateKeyboardEvent(source, CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode), false); // Key up
        CGEventSetFlags(keyUpEvent, flags);
        CGEventPost(kCGHIDEventTap, keyUpEvent);
        CFRelease(keyUpEvent);
    }

    CFRelease(source);
}

void MacOSShortcutHandler::saveShortcut(const std::string& sumKeyCodes) {
    std::istringstream shortcutStream(sumKeyCodes);
    std::string keyPart;
    std::string key;
    std::string value;

    std::getline(shortcutStream, keyPart, ',');
    key = keyPart[0];
    // std::cout << "Here is the key: " << key << ". and here is the keyPart: " << keyPart << std::endl;

    std::getline(shortcutStream, keyPart, ',');
    value = keyPart;
    // std::cout << "Here is the value: " << value << std::endl;

    std::string section = "Shortcuts";
    UTILS::updateYamlFile(section, key, value);
}
