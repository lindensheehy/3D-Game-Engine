#pragma once


// This is the list of keycodes my program tracks.
// These values coorespond to both the given values from Windows, as well as the indexing of the keyStates array
enum class KeyCode : unsigned int {

    // This is just a "no key" value
    NONE = 0x00,

    // Letter Keys
    A = 0x41,
    B = 0x42,
    C = 0x43,
    D = 0x44,
    E = 0x45,
    F = 0x46,
    G = 0x47,
    H = 0x48,
    I = 0x49,
    J = 0x4A,
    K = 0x4B,
    L = 0x4C,
    M = 0x4D,
    N = 0x4E,
    O = 0x4F,
    P = 0x50,
    Q = 0x51,
    R = 0x52,
    S = 0x53,
    T = 0x54,
    U = 0x55,
    V = 0x56,
    W = 0x57,
    X = 0x58,
    Y = 0x59,
    Z = 0x5A,

    // Number Keys
    NUM_0 = 0x30,
    NUM_1 = 0x31,
    NUM_2 = 0x32,
    NUM_3 = 0x33,
    NUM_4 = 0x34,
    NUM_5 = 0x35,
    NUM_6 = 0x36,
    NUM_7 = 0x37,
    NUM_8 = 0x38,
    NUM_9 = 0x39,

    // Misc Keys
    SPACE = 0x20,
    TAB = 0x09,
    ENTER = 0x0D,
    ESCAPE = 0x1B,
    BACKSPACE = 0x08,
    CAPSLOCK = 0x14,
    PERIOD = 0xBE,
    MINUS = 0xBD,

    // Function Keys
    F1 = 0x70,
    F2 = 0x71,
    F3 = 0x72,
    F4 = 0x73,
    F5 = 0x74,
    F6 = 0x75,
    F7 = 0x76,
    F8 = 0x77,
    F9 = 0x78,
    F10 = 0x79,
    F11 = 0x7A,
    F12 = 0x7B,

    // Modifier Keys
    CONTROL = 0x11,
    SHIFT = 0x10,
    ALT = 0xA4,

    // Arrow Keys
    ARROWUP = 0x26,
    ARROWDOWN = 0x28,
    ARROWLEFT = 0x25,
    ARROWRIGHT = 0x27

};

// Helper functions for KeyCodes
bool hasValidChar(KeyCode key);
char keyCodeToChar(KeyCode key);
