#include "main.hpp"
#include <ApplicationServices/ApplicationServices.h>

int main() {
    // Create and post the "Shift" key press event
    CGEventRef event1 = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)56, true);
    CGEventPost(kCGHIDEventTap, event1);

    // Create and post the "z" key press event
    CGEventRef event2 = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)6, true);
    CGEventPost(kCGHIDEventTap, event2);

    // Create and post the "Shift" key release event
    CGEventRef event3 = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)56, false);
    CGEventPost(kCGHIDEventTap, event3);

    // Create and post the "z" key release event
    CGEventRef event4 = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)6, false);
    CGEventPost(kCGHIDEventTap, event4);

    // CFRelease(event4);
    // CFRelease(event3);
    // CFRelease(event2);
    // CFRelease(event1);

    return 0;
}

