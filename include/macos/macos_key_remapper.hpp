#pragma once

#include "key_remapper_interface.hpp"
#include "macos/macos_shortcut_handler.hpp"
#include "macos_exception_handling.hpp"
#include "macos_virtual_keycodes.hpp"
#include "yaml-cpp/node/node.h"
#include "yaml_handler.hpp"

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CFMachPort.h>
#include <CoreGraphics/CGEvent.h>
#include <CoreGraphics/CGEventTypes.h>
#include <string>

class MacOSKeyRemapper : public KeyRemapperInterface {
public:
    // MacOSKeyRemapper();
    void initialize() override;
    void run() override;
    void cleanup() override;
    static void reverseCapsLockStartUp();

private:
    static MacOSKeyRemapper* instance;

    MacOSShortcutHandler shortcutHandler;
    
    static CGEventRef eventCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon);

    CFMachPortRef eventTap = nullptr;
    CFRunLoopSourceRef runLoopSource = nullptr;
    bool actionMode = true;
    bool alphaMode = false;
    bool recordMode = false;
    static bool capsLockPhase;
    static std::string sumKeyCodes;
};
