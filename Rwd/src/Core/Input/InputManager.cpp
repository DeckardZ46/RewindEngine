#include "pch.h"
#include "InputManager.h"

namespace Rwd{
InputManager::~InputManager() {
    shutdown();
}

void InputManager::init() {
    // nothing to do
}

void InputManager::shutdown() {
    // clear input states
    std::memset(m_inputState.keys, 0, sizeof(m_inputState.keys));
    std::memset(m_inputState.prevKeys, 0, sizeof(m_inputState.prevKeys));
    std::memset(m_inputState.mouseButtons, 0, sizeof(m_inputState.mouseButtons));
    std::memset(m_inputState.prevMouseButtons, 0, sizeof(m_inputState.prevMouseButtons));
}

void InputManager::update() {
    std::memcpy(m_inputState.prevKeys, m_inputState.keys, sizeof(m_inputState.keys));
    std::memcpy(m_inputState.prevMouseButtons, m_inputState.mouseButtons, sizeof(m_inputState.mouseButtons));
    m_inputState.prevMouseX = m_inputState.mouseX;
    m_inputState.prevMouseY = m_inputState.mouseY;
}

bool InputManager::isKeyPressed(RwdKeyCode key) {
    uint16 keyIndex = static_cast<uint16>(key);
    if (keyIndex < MAX_KEYCODE_COUNT) {
        return m_inputState.keys[keyIndex];
    }
    return false;
}

bool InputManager::isMouseButtonPressed(RwdMouseButton button) {
    uint8 buttonIndex = static_cast<uint8>(button);
    if (buttonIndex < MAX_MOUSEBUTTON_COUNT) {
        return m_inputState.mouseButtons[buttonIndex];
    }
    return false;
}

void InputManager::onKeyPress(RwdKeyCode key) {
    uint16 keyIndex = static_cast<uint16>(key);
    if (keyIndex < MAX_KEYCODE_COUNT) {
        m_inputState.keys[keyIndex] = true;
    }
    NLOGD("Key Pressed: {0}", keyIndex);
}

void InputManager::onKeyRelease(RwdKeyCode key) {
    uint16 keyIndex = static_cast<uint16>(key);
    if (keyIndex < MAX_KEYCODE_COUNT) {
        m_inputState.keys[keyIndex] = false;
    }
    NLOGD("Key Released: {0}", keyIndex);
}

void InputManager::onMouseButtonPress(RwdMouseButton button) {
    uint8 buttonIndex = static_cast<uint8>(button);
    if (buttonIndex < MAX_MOUSEBUTTON_COUNT) {
        m_inputState.mouseButtons[buttonIndex] = true;
    }
    NLOGD("Mouse Button Pressed: {0}", buttonIndex);
}

void InputManager::onMouseButtonRelease(RwdMouseButton button) {
    uint8 buttonIndex = static_cast<uint8>(button);
    if (buttonIndex < MAX_MOUSEBUTTON_COUNT) {
        m_inputState.mouseButtons[buttonIndex] = false;
    }
    NLOGD("Mouse Button Released: {0}", buttonIndex);
}

void InputManager::onMouseMove(float xPos, float yPos) {
    m_inputState.mouseX = xPos;
    m_inputState.mouseY = yPos;
    NLOGD("Mouse Moved to: ({0}, {1})", xPos, yPos);
}

void InputManager::onMouseScroll(float xOffset, float yOffset) {
    NLOGD("Mouse Scrolled: ({0}, {1})", xOffset, yOffset);
}
} // namespace Rwd