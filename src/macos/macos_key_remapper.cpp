#include "macos_key_remapper.hpp"
#include "macos_shortcut_handler.hpp"
#include "macos_yaml_handler.hpp"

#include <CoreGraphics/CGEventTypes.h>
#include <chrono>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>

// initializing static methods
MacOSKeyRemapper* MacOSKeyRemapper::instance = nullptr;
bool MacOSKeyRemapper::capsLockPhase = false;
std::string MacOSKeyRemapper::sumKeyCodes = "";

CGEventRef MacOSKeyRemapper::eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    CGEventFlags flags = CGEventGetFlags(event);
    
    if (type != kCGEventKeyDown && type != kCGEventFlagsChanged) {
        return event;
    }

    MacOSKeyRemapper* remapper = instance;

    // Toggle action mode
    if (type == kCGEventKeyDown && keyCode == UTILS::ACTION && (flags & kCGEventFlagMaskCommand)) {
        remapper->actionMode = !remapper->actionMode;
        std::cout << "\nAction mode: " << (remapper->actionMode ? "ON\n" : "OFF\n") << std::endl;
        return NULL; // Consume the event
    }

    // Toggle capsLockPhase
    if (type == kCGEventFlagsChanged && (keyCode == 57 || keyCode == 0)) {
        if (remapper->actionMode) {
            remapper->capsLockPhase = !remapper->capsLockPhase;
            std::cout << "\nCaps lock phase: " << (remapper->capsLockPhase ? "ON\n" : "OFF\n") << std::endl;
        }
        return event;
    }

    // Toggle alpha mode
    if (type == kCGEventKeyDown && keyCode == UTILS::ALPHA && remapper->capsLockPhase) {
        remapper->alphaMode = !remapper->alphaMode;
        std::cout << "\nAlpha Mode: " << (remapper->alphaMode ? "ON\n" : "OFF\n");
        return NULL;
    }

    // Toggle record mode
    if (type == kCGEventKeyDown && keyCode == UTILS::RECORD && remapper->capsLockPhase && !remapper->alphaMode) {
        remapper->recordMode = !remapper->recordMode;
        std::cout << "\nRecord mode: " << (remapper->recordMode ? "ON\n" : "OFF\n") << std::endl;
        return NULL;
    }

    // 'if' for when action mode is activated to handle remappings and shortcuts
    if (remapper->capsLockPhase && remapper->actionMode && !remapper->alphaMode && !remapper->recordMode && type == kCGEventKeyDown) {
        if (keyCode == UTILS::LEFT) {
            CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, 123);
        } else if (keyCode == UTILS::DOWN) {
            CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, 125);
        } else if (keyCode == UTILS::UP) {
            CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, 126);
        } else if (keyCode == UTILS::RIGHT) {
            CGEventSetIntegerValueField(event, kCGKeyboardEventKeycode, 124);
        } else {
             // Handle shortcuts
            auto keyStrOpt = KeyCodes::getStringKey(keyCode);
            if (keyStrOpt) {
                std::string keyStr = keyStrOpt.value();
                MacOSShortcutHandler::handleShortcut(keyStr);
            }
        }

        return event;

    // 'else if' for when the recording mode is activated
    } else if (remapper->capsLockPhase && remapper->actionMode && !remapper->alphaMode && remapper->recordMode && type == kCGEventKeyDown) {
        auto recordingItemOpt = KeyCodes::getStringKey(keyCode);
        if (recordingItemOpt) {
            std::string recordingItem = recordingItemOpt.value();

            if (flags & kCGEventFlagMaskCommand) {
                recordingItem = "COMMAND+" + recordingItem;
            }
            if (flags & kCGEventFlagMaskControl) {
                recordingItem = "CONTROL+" + recordingItem;
            }
            if (flags & kCGEventFlagMaskShift) {
                recordingItem = "SHIFT+" + recordingItem;
            }
            if (flags & kCGEventFlagMaskAlternate) {
                recordingItem = "OPTION+" + recordingItem;
            }

            sumKeyCodes += recordingItem;
        }

        return event;
    }

    if (!sumKeyCodes.empty()) {
        std::cout << "Here is the sumKeyCodes: " <<  sumKeyCodes << std::endl;
        MacOSShortcutHandler::saveShortcut(sumKeyCodes);
    }
    sumKeyCodes = "";

    return event;
}


void MacOSKeyRemapper::initialize() {
    try {
        UTILS::initialize();
        MacOSShortcutHandler::initialize();
    } catch (const std::exception& e) {
        std::cerr << "Initialization error: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    instance = this;  // Set the static instance pointer

    eventTap = CGEventTapCreate(
        kCGSessionEventTap,
        kCGHeadInsertEventTap,
        kCGEventTapOptionDefault,
        CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged),
        eventCallback,
        NULL
    );

    runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);

    CGEventTapEnable(eventTap, true);
}

void MacOSKeyRemapper::run() {
    std::cout << "Key remapping started. Press Ctrl+C to exit." << std::endl;
    CFRunLoopRun();
}

void MacOSKeyRemapper::cleanup() {
    if (eventTap) {
        CFMachPortInvalidate(eventTap);
        CFRelease(eventTap);
        eventTap = nullptr;
    }
    if (runLoopSource) {
        CFRunLoopRemoveSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
        CFRelease(runLoopSource);
        runLoopSource = nullptr;
    }
}

void MacOSKeyRemapper::reverseCapsLockStartUp() {
    capsLockPhase = !capsLockPhase;
}
