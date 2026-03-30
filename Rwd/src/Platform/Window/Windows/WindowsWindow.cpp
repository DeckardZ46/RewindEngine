#include <pch.h>
#include <glad.h>
#include "Rwd.h"
#include "WindowsWindow.h"
#include "Core/Input/glfw/KeyMapGLFW.h"
#include "Core/Input/glfw/MouseMapGLFW.h"

namespace Rwd {
static bool s_glfwInit = false;

static void GLFWErrorCallback(int error, const char *description) {
    NLOGE("GLFW Error ({0}): {1}", error, description);
}

void FramebufferSizeChange_cb(GLFWwindow *window, int width, int height);

WindowsWindow::WindowsWindow(const WindowData &wdata) : m_data(wdata) {
    // nothing to do
}

WindowsWindow::~WindowsWindow() {
    shutdown();
}

void WindowsWindow::init() {
    NLOGI("Creating Windows window [{0}]...\nwidth: {1}, height: {2}", m_data.title, m_data.width, m_data.height);

    // init glfw
    if (!s_glfwInit) {
        s_glfwInit = glfwInit();
        Rwd_ASSERT(s_glfwInit, "glfw initialize failed!");

        // opengl settings
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Rwd_OGL_VER_MAJ);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Rwd_OGL_VER_MIN);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback(GLFWErrorCallback);
    }

    // create window
    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    Rwd_ASSERT(m_window != nullptr, "Failed to create glfw window!");
    glfwMakeContextCurrent(m_window);
    setVSync(true);
    hwnd = glfwGetWin32Window(m_window);

    // init OpenGL
    int stat = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Rwd_ASSERT(stat, "Failed to initialize GLAD!");

    // set callback funtions
    glfwSetWindowUserPointer(m_window, &m_data);
    setWindowCallBack();

    // calculate dpi scale
    uint dpi = GetDpiForWindow(hwnd);
    m_dpiScale = dpi / 96.0f;
    int logicW = static_cast<int>(m_data.width * m_dpiScale);
    int logicH = static_cast<int>(m_data.height * m_dpiScale);
    glfwSetWindowSize(m_window, logicW, logicH);
}

void WindowsWindow::shutdown() {
    // destroy all windows
    glfwDestroyWindow(m_window);
    m_window = nullptr;

    // terminate glfw program
    glfwTerminate();
}

void WindowsWindow::update() {
    glfwPollEvents();
    // TODO: tmp
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowsWindow::endFrame() {
    glfwSwapBuffers(m_window);
}

void WindowsWindow::setVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
        m_isVSync = true;
    } else {
        glfwSwapInterval(0);
        m_isVSync = false;
    }
}

void WindowsWindow::setWindowCallBack() {

    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeChange_cb);

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        NLOGI("window size CB");
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        NLOGI("window close CB");
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        switch (action) {
        case GLFW_PRESS:
            RwdRuntime::Get().getInputManager().onKeyPress(GLFWKeyToRwdKeyCode(key));
            break;
        case GLFW_RELEASE:
            RwdRuntime::Get().getInputManager().onKeyRelease(GLFWKeyToRwdKeyCode(key));
            break;
        case GLFW_REPEAT:
            // handle key repeat if needed
            break;
        default:
            break;
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow *window, unsigned int c) {
        // handle character input if needed
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
        switch (action) {
        case GLFW_PRESS:
            RwdRuntime::Get().getInputManager().onMouseButtonPress(static_cast<RwdMouseButton>(button));
            break;
        case GLFW_RELEASE:
            RwdRuntime::Get().getInputManager().onMouseButtonRelease(static_cast<RwdMouseButton>(button));
            break;
        default:
            break;
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
        RwdRuntime::Get().getInputManager().onMouseScroll(static_cast<float>(xOffset), static_cast<float>(yOffset));
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
        RwdRuntime::Get().getInputManager().onMouseMove(static_cast<float>(xPos), static_cast<float>(yPos));
    });
}

bool WindowsWindow::isClose() const {
    if (glfwWindowShouldClose(m_window)) {
        return true;
    } else {
        return false;
    }
}

void FramebufferSizeChange_cb(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

} // namespace Rwd