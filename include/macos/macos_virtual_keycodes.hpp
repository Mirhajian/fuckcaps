#pragma once

#include <map>
#include <optional>
#include <string>

class KeyCodes {
public:
    static std::optional<int> getKeyCode(const std::string& input);
    static std::optional<std::string> getStringKey(const int keyCode);

private:
    // Thanks to the people at http://ritter.ist.psu.edu/, I was able
    // to find the virtual keycodes for the macOS, there is no official
    // document by Apple that provides the keycode numbers. if you know
    // of a better list of keycodes, I'd be happy to have you as a contributor.
    // Here is the code that I borrowed from:
    // http://ritter.ist.psu.edu/projects/RUI/macosx/rui.c
    static std::multimap<std::string, int> keyCodeMap;
};
