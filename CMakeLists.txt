cmake_minimum_required(VERSION 3.12)
project(fuckcaps VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(PLATFORM_SOURCES
        src/macos/macos_key_remapper.cpp
        src/macos/macos_virtual_keycodes.cpp
        src/macos/macos_yaml_handler.cpp
        src/macos/macos_exception_handling.cpp
        src/macos/macos_shortcut_handler.cpp
    )
    
    # find the ApplicationServices framework
    find_library(APPLICATION_SERVICES_FRAMEWORK ApplicationServices)
    if (APPLICATION_SERVICES_FRAMEWORK)
        set(PLATFORM_LIBS
          ${APPLICATION_SERVICES_FRAMEWORK}
        )
    else()
        message(FATAL_ERROR "ApplicationServices framework not found")
    endif()

    # find and link the ncurses library
    find_package(Curses REQUIRED)
    set(PLATFORM_LIBS ${PLATFORM_LIBS} ${CURSES_LIBRARIES})

    # fetch the FTXUI
    include(FetchContent)
    FetchContent_Declare(
        ftxui
        GIT_REPOSITORY /opt/ftxui
        # GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(ftxui)

    # fetch yaml-cpp
    FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY /opt/yaml-cpp
        # GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(yaml-cpp)

elseif(UNIX AND NOT APPLE)
    set(PLATFORM_SOURCES
        src/linux/linux_key_remapper.cpp
    )
    # Find and link the ncurses library
    find_package(Curses REQUIRED)
    set(PLATFORM_LIBS ${CURSES_LIBRARIES})
endif()

add_executable(fuckcaps
    src/main.cpp
    ${PLATFORM_SOURCES}
    src/common/unix_config_setup.cpp
    src/common/terminal_ui_handler.cpp
    src/common/yaml_handler.cpp
)

# set the working directory to the models directory
# set_target_properties(fuckcaps PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/models"
# )

target_include_directories(
    fuckcaps 
    PRIVATE include src
    PRIVATE include src/common/
    PRIVATE include include/macos/
    PRIVATE ${yaml-cpp_SOURCE_DIR}/include
)

# link platform-specific libraries
target_link_libraries(fuckcaps 
    PRIVATE ${PLATFORM_LIBS}
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PUBLIC yaml-cpp::yaml-cpp
)

# message(STATUS "YAML-CPP Include Directory: ${yaml-cpp_SOURCE_DIR}/include")

# Add installation rules
install(TARGETS fuckcaps DESTINATION bin)

if(APPLE)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path" FORCE)
endif()
