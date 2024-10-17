// #include "terminal_ui_handler.hpp"
#include "unix_config_setup.hpp"
#include "yaml_handler.hpp"

#include <iostream>
#include <memory>
#include <vector>

#ifdef __APPLE__
#include "macos/macos_key_remapper.hpp"
#include "macos/macos_yaml_handler.hpp"
#elif __linux__
#include "linux/linux_key_remapper.hpp"
#else
#error "Unsupported platform"
#endif


bool isCapsLockOn() {
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventFlagMaskAlphaShift) != 0;
}

int main(int argc, char *argv[]) {
    ConfigSetup::setupConfig();
    YamlHandler::loadYamlConfigFile();

    // using namespace TerminalUiHandler;
    // TerminalUiHandler session;
    // session.drawScreen();

    std::unique_ptr<KeyRemapperInterface> remapper;

#ifdef __APPLE__
    remapper = std::make_unique<MacOSKeyRemapper>();

    if(isCapsLockOn()) {
        MacOSKeyRemapper::reverseCapsLockStartUp();
        std::cout << "Caps Lock is ON at startup." << std::endl;
    }

#elif __linux__
    remapper = std::make_unique<LinuxKeyRemapper>();
#endif

    try {
        remapper->initialize();
        remapper->run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    remapper->cleanup();

    return 0;
}
