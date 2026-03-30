/**
 * < Rewind Engine > KeyInput.h
 * Author: DeckardZ46
 * Date: 2025/09/01
 * Note: Key Input Definitions of Rewind Engine
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

#define MAX_KEYCODE_COUNT 128

namespace Rwd {
/**
 * here we use USB HID Usage ID as keycode
 * reference: https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 */

enum class RwdKeyCode : uint16 {
    AnyKey = 0x00,

    // 0x04 – 0x1D letters
    A = 0x04,
    B = 0x05,
    C = 0x06,
    D = 0x07,
    E = 0x08,
    F = 0x09,
    G = 0x0A,
    H = 0x0B,
    I = 0x0C,
    J = 0x0D,
    K = 0x0E,
    L = 0x0F,
    M = 0x10,
    N = 0x11,
    O = 0x12,
    P = 0x13,
    Q = 0x14,
    R = 0x15,
    S = 0x16,
    T = 0x17,
    U = 0x18,
    V = 0x19,
    W = 0x1A,
    X = 0x1B,
    Y = 0x1C,
    Z = 0x1D,

    // 0x1E – 0x27 numbers
    Num1 = 0x1E,
    Num2 = 0x1F,
    Num3 = 0x20,
    Num4 = 0x21,
    Num5 = 0x22,
    Num6 = 0x23,
    Num7 = 0x24,
    Num8 = 0x25,
    Num9 = 0x26,
    Num0 = 0x27,

    // 0x28 – 0x39 control keys & symbol keys
    Enter           = 0x28,
    Escape          = 0x29,
    Backspace       = 0x2A,
    Tab             = 0x2B,
    Space           = 0x2C,
    Minus           = 0x2D, // -
    Equal           = 0x2E, // =
    LeftBracket     = 0x2F, // [
    RightBracket    = 0x30, // ]
    Backslash       = 0x31, // (backslash)
    Semicolon       = 0x33, // ;
    Apostrophe      = 0x34, // '
    Grave           = 0x35, // `
    Comma           = 0x36, // ,
    Period          = 0x37, // .
    Slash           = 0x38, // /
    CapsLock        = 0x39,

    // 0x3A – 0x45 F1-F12
    F1  = 0x3A,
    F2  = 0x3B,
    F3  = 0x3C,
    F4  = 0x3D,
    F5  = 0x3E,
    F6  = 0x3F,
    F7  = 0x40,
    F8  = 0x41,
    F9  = 0x42,
    F10 = 0x43,
    F11 = 0x44,
    F12 = 0x45,

    // 0x46 – 0x53 others
    PrintScreen     = 0x46,
    ScrollLock      = 0x47,
    Pause           = 0x48,
    Insert          = 0x49,
    Home            = 0x4A,
    PageUp          = 0x4B,
    Delete          = 0x4C,
    End             = 0x4D,
    PageDown        = 0x4E,
    RightArrow      = 0x4F,
    LeftArrow       = 0x50,
    DownArrow       = 0x51,
    UpArrow         = 0x52,
    NumLock         = 0x53
};

} // namespace Rwd