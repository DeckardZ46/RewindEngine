/**
 * < Rewind Engine > KeyMapGLFW.h
 * Author: DeckardZ46
 * Date: 2025/10/28
 * Note: Key mapping between Rewind Engine and GLFW
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

#include "Core/Input/KeyInput.h"
#include <glfw3.h>

namespace Rwd {
[[nodiscard]] inline constexpr RwdKeyCode GLFWKeyToRwdKeyCode(int glfwKey) noexcept{
    // A-ZA
    if (glfwKey >= GLFW_KEY_A && glfwKey <= GLFW_KEY_Z) return static_cast<RwdKeyCode>(static_cast<uint16>(RwdKeyCode::A) + (glfwKey - GLFW_KEY_A));
    
    // 0-9
    if (glfwKey >= GLFW_KEY_0 && glfwKey <= GLFW_KEY_9) return static_cast<RwdKeyCode>(static_cast<uint16>(RwdKeyCode::Num0) + (glfwKey - GLFW_KEY_0));

    switch (glfwKey) {
        // control keys & symbol keys
        case GLFW_KEY_ENTER:         return RwdKeyCode::Enter;
        case GLFW_KEY_ESCAPE:        return RwdKeyCode::Escape;
        case GLFW_KEY_BACKSPACE:     return RwdKeyCode::Backspace;
        case GLFW_KEY_TAB:           return RwdKeyCode::Tab;
        case GLFW_KEY_SPACE:         return RwdKeyCode::Space;
        case GLFW_KEY_MINUS:         return RwdKeyCode::Minus;
        case GLFW_KEY_EQUAL:         return RwdKeyCode::Equal;
        case GLFW_KEY_LEFT_BRACKET:  return RwdKeyCode::LeftBracket;
        case GLFW_KEY_RIGHT_BRACKET: return RwdKeyCode::RightBracket;
        case GLFW_KEY_BACKSLASH:     return RwdKeyCode::Backslash;
        case GLFW_KEY_SEMICOLON:     return RwdKeyCode::Semicolon;
        case GLFW_KEY_APOSTROPHE:    return RwdKeyCode::Apostrophe;
        case GLFW_KEY_GRAVE_ACCENT:  return RwdKeyCode::Grave;
        case GLFW_KEY_COMMA:         return RwdKeyCode::Comma;
        case GLFW_KEY_PERIOD:        return RwdKeyCode::Period;
        case GLFW_KEY_SLASH:         return RwdKeyCode::Slash;
        case GLFW_KEY_CAPS_LOCK:     return RwdKeyCode::CapsLock;

        // F1-F12
        case GLFW_KEY_F1:  return RwdKeyCode::F1;
        case GLFW_KEY_F2:  return RwdKeyCode::F2;
        case GLFW_KEY_F3:  return RwdKeyCode::F3;
        case GLFW_KEY_F4:  return RwdKeyCode::F4;
        case GLFW_KEY_F5:  return RwdKeyCode::F5;
        case GLFW_KEY_F6:  return RwdKeyCode::F6;
        case GLFW_KEY_F7:  return RwdKeyCode::F7;
        case GLFW_KEY_F8:  return RwdKeyCode::F8;
        case GLFW_KEY_F9:  return RwdKeyCode::F9;
        case GLFW_KEY_F10: return RwdKeyCode::F10;
        case GLFW_KEY_F11: return RwdKeyCode::F11;
        case GLFW_KEY_F12: return RwdKeyCode::F12;

        // others
        case GLFW_KEY_PRINT_SCREEN:  return RwdKeyCode::PrintScreen;
        case GLFW_KEY_SCROLL_LOCK:   return RwdKeyCode::ScrollLock;
        case GLFW_KEY_PAUSE:         return RwdKeyCode::Pause;
        case GLFW_KEY_INSERT:        return RwdKeyCode::Insert;
        case GLFW_KEY_HOME:          return RwdKeyCode::Home;
        case GLFW_KEY_PAGE_UP:       return RwdKeyCode::PageUp;
        case GLFW_KEY_DELETE:        return RwdKeyCode::Delete;
        case GLFW_KEY_END:           return RwdKeyCode::End;
        case GLFW_KEY_PAGE_DOWN:     return RwdKeyCode::PageDown;
        case GLFW_KEY_RIGHT:         return RwdKeyCode::RightArrow;
        case GLFW_KEY_LEFT:          return RwdKeyCode::LeftArrow;
        case GLFW_KEY_DOWN:          return RwdKeyCode::DownArrow;
        case GLFW_KEY_UP:            return RwdKeyCode::UpArrow;
        case GLFW_KEY_NUM_LOCK:      return RwdKeyCode::NumLock;

        // Add more key mappings as needed
        default:                     return RwdKeyCode::AnyKey; // Unknown key
    }
}
} // namespace Rwd