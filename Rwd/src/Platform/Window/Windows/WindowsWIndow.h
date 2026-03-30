/**
 * < Rewind Engine > WindowsWindow.h
 * Author: DeckardZ46
 * Date: 2024/11/27
 * Note: Rewind Window for Windows platform
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32

#include <glfw3.h>
#include <glfw3native.h>
#include <Details/Window/RwdWindow.h>

namespace Rwd {
class WindowsWindow final : public WindowBase {
  public:
    WindowsWindow(const WindowData &wdata);
    ~WindowsWindow();

    inline uint32_t getWidth() const override {
        return m_data.width;
    }
    inline uint32_t getHeight() const override {
        return m_data.height;
    }

    inline bool isVSync() const override {
        return m_isVSync;
    }
    bool isClose() const override;

  private:
    void init();
    void shutdown();

    void update() override;
    void endFrame() override;
    inline void setVSync(bool enabled) override;
    void *getNativeWindow() const override {
        return static_cast<void *>(m_window);
    }
    void setWindowCallBack();

  private:
    bool m_isVSync;
    GLFWwindow *m_window;
    WindowData m_data;
    HWND hwnd;
};
} // namespace Rwd