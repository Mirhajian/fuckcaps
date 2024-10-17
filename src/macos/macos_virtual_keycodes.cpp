#include "macos_virtual_keycodes.hpp"

std::optional<int> KeyCodes::getKeyCode(const std::string& input) {
    // auto it = keyCodeMap.find(input);  // DEPRICATED, This is for std::map
    auto range = keyCodeMap.equal_range(input);

    if (range.first != range.second) {
        return range.first->second;
    } else {
        return std::nullopt;
    }
}

std::optional<std::string> KeyCodes::getStringKey(const int keyCode) {
    for (const auto& pair : keyCodeMap) {
        if (pair.second == keyCode) {
        return pair.first;
        }
    }

    return std::nullopt;
}

std::multimap<std::string, int> KeyCodes::keyCodeMap = {
    {"a", 0},
    {"s", 1},
    {"d", 2},
    {"f", 3},
    {"h", 4},
    {"g", 5},
    {"z", 6},
    {"x", 7},
    {"c", 8},
    {"v", 9},
    // skip case 10, this does not exist
    {"b", 11},
    {"q", 12},
    {"w", 13},
    {"e", 14},
    {"r", 15},
    {"y", 16},
    {"t", 17},
    {"1", 18},
    {"2", 19},
    {"3", 20},
    {"4", 21},
    {"6", 22},
    {"5", 23},
    {"=", 24},
    {"9", 25},
    {"7", 26},
    {"-", 27},
    {"8", 28},
    {"0", 29},
    {"]", 30},
    {"o", 31},
    {"u", 32},
    {"[", 33},
    {"i", 34},
    {"p", 35},
    {"RETURN", 36},
    {"l", 37},
    {"j", 38},
    {"'", 39},
    {"k", 40},
    {";", 41},
    {"\\", 42},
    {",", 43},
    {"/", 44},
    {"n", 45},
    {"m", 46},
    {".", 47},
    {"TAB", 48},
    {"SPACE", 49},
    {"`", 50},
    {"DELETE", 51},
    {"ENTER", 52},
    {"ESCAPE", 53},
    // skip some codes, assuming they are reserved
    {".", 65},
    {"*", 67},
    {"+", 69},
    {"CLEAR", 71},
    {"/", 75},
    {"ENTER", 76},   // numberpad on full keyboard
    {"-", 78},
    {"=", 81},
    {"0", 82},
    {"1", 83},
    {"2", 84},
    {"3", 85},
    {"4", 86},
    {"5", 87},
    {"6", 88},
    {"7", 89},
    {"8", 91},
    {"9", 92},
    {"F5", 96},
    {"F6", 97},
    {"F7", 98},
    {"F3", 99},
    {"F8", 100},
    {"F9", 101},
    {"F11", 103},
    {"F13", 105},
    {"F14", 107},
    {"F10", 109},
    {"F12", 111},
    {"F15", 113},
    {"HELP", 114},
    {"HOME", 115},
    {"PGUP", 116},
    {"DELETE", 117},  // full keyboard right side numberpad
    {"F4", 118},
    {"END", 119},
    {"F2", 120},
    {"PGDN", 121},
    {"F1", 122},
    {"LEFT", 123},
    {"RIGHT", 124},
    {"DOWN", 125},
    {"UP", 126},
};
