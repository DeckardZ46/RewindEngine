/**
 * < Rewind Engine > Rwd.h
 * Author: DeckardZ46
 * Date: 2024/09/09
 * Note: This is header file for Rewind Engine Runtime
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#include "Core/Input/InputManager.h"
#include "Details/Window/RwdWindow.h"

namespace Rwd {
class RwdRuntime {
    friend class RwdApp;
    friend class EditorUI;

  private:
    RwdRuntime();
    RwdRuntime(const RwdRuntime &) = delete;
    RwdRuntime(RwdRuntime &&) = delete;
    RwdRuntime &operator=(const RwdRuntime &) = delete;
    RwdRuntime &operator=(RwdRuntime &&) = delete;

  public:
    ~RwdRuntime();

    /**
     * public functions
     */
    inline static RwdRuntime &Get() {
        static RwdRuntime s_Runtime;
        return s_Runtime;
    }

    // input system
    inline InputManager &getInputManager() const {
        return *m_inputManager;
    }

    // window system
    inline WindowBase &getWindow() const {
        return *m_window;
    }

  private:
    /**
     * private functions
     */
    void init();
    void shutdown();

    void tick();
    void flush();

    // window system
    inline void *getNativeWindow() {
        return m_window->getNativeWindow();
    }

  private:
    /**
     * private members
     */
    // status
    bool m_initialized = false;

    // managers & systems
    RUniquePtr<InputManager> m_inputManager;
    RUniquePtr<WindowBase> m_window;
};
} // namespace Rwd