#include <pch.h>
#include <Rwd.h>
#include "EditorUI.h"

#ifdef Rwd_PLAT_WINDOWS
#include <glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif // Rwd_PLAT_WINDOWS

#include "Panels/ConsolePanel.h"

namespace Rwd {
EditorUI::EditorUI() {
    ELOGD("Initializing EditorUI...");
    /**
     *  create imgui context
     */
    IMGUI_CHECKVERSION();

    if (!ImGui::GetCurrentContext()) {
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        ImGui::StyleColorsDark();
        float dpiscale = RwdRuntime::Get().getWindow().getDPIScale();
        io.Fonts->AddFontFromFileTTF("../../../../Assets/Fonts/Cousine-Regular.ttf", 16 * dpiscale);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        ImGuiStyle& style = ImGui::GetStyle();
        style = ImGuiStyle();
        style.ScaleAllSizes(dpiscale);
    }

    /**
     *  init imgui render backend
     */
    EDITOR_ASSERT(ImGui::GetCurrentContext() != nullptr,
                "Cannot get imgui context before init render backend for imgui!");
    // windows
#ifdef Rwd_PLAT_WINDOWS
    void *glfwWindowPtr = RwdRuntime::Get().getNativeWindow();
    EDITOR_ASSERT(glfwWindowPtr != nullptr, "ImGuiUI: get native glfw window failed!");
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(glfwWindowPtr), true);
    ImGui_ImplOpenGL3_Init("#version 460");
#endif // Rwd_PLAT_WINDOWS

    // other platforms
    // ...

    // init font
}

EditorUI::~EditorUI() {
    // clear imgui render backend
#ifdef Rwd_PLAT_WINDOWS
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
#endif // Rwd_PLAT_WINDOWS

    // destroy context
    ImGui::DestroyContext();
}

void EditorUI::init() {
    // init panels
    auto consolePanel = new ConsolePanel("ConsolePanel");
    m_panels.emplace_back(std::move(consolePanel));
}

void EditorUI::clear() {
    // clear panels
    for (auto panel : m_panels) {
        if (panel != nullptr) {
            delete panel;
            panel = nullptr;
        }
    }
    m_panels.clear();
    n_vector<PanelBase *>().swap(m_panels);
}

void EditorUI::update() {
#ifdef Rwd_PLAT_WINDOWS
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
#endif // Rwd_PLAT_WINDOWS

    ImGui::NewFrame();
    if (m_panels.size() > 0) {
        for (auto panel : m_panels) {
            panel->update();
        }
    }
}

void EditorUI::draw() {
    if (m_panels.size() > 0) {
        for (auto panel : m_panels) {
            EDITOR_ASSERT(panel != nullptr, "Editor UI: draw panel failed! Panel is null.");
            panel->draw();
        }
    }
    ImGui::Render();

#ifdef Rwd_PLAT_WINDOWS
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // Rwd_PLAT_WINDOWS
}

} // namespace Rwd