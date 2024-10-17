#include <ApplicationServices/ApplicationServices.h>

bool isCapsLockOn() {
    // Get the current state of the keyboard
    CGEventSourceRef eventSource = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    if (!eventSource) {
        fprintf(stderr, "Failed to create event source\n");
        return false;
    }

    // Get the state of the Caps Lock key
    bool capsLockOn = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState) & kCGEventFlagMaskAlphaShift;

    CFRelease(eventSource);
    return capsLockOn;
}

int main() {
    if (isCapsLockOn()) {
        printf("Caps Lock is ON\n");
    } else {
        printf("Caps Lock is OFF\n");
    }

    return 0;
}
