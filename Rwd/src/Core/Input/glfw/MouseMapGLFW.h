/**
 * < Rewind Engine > MouseMapGLFW.h
 * Author: DeckardZ46
 * Date: 2025/10/28
 * Note: Mouse mapping between Rewind Engine and GLFW
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

#include "Core/Input/MouseInput.h"
#include <glfw3.h>

namespace Rwd{
[[nodiscard]] inline constexpr RwdMouseButton GLFWMouseButtonToRwdMouseButton(int glfwButton) noexcept{
    switch (glfwButton) {
        case GLFW_MOUSE_BUTTON_LEFT:      return RwdMouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT:     return RwdMouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE:    return RwdMouseButton::Middle;
        case GLFW_MOUSE_BUTTON_4:         return RwdMouseButton::ButtonX1;
        case GLFW_MOUSE_BUTTON_5:         return RwdMouseButton::ButtonX2;
        default:                          return RwdMouseButton::AnyMouseButton;
    }
}
} // namespace Rwd 