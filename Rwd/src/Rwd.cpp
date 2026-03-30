#include <pch.h>
#include "Rwd.h"

namespace Rwd {
RwdRuntime::RwdRuntime() {
    // RAII
    init();
}

RwdRuntime::~RwdRuntime() = default;

void RwdRuntime::init() {
    if (m_initialized) {
        return;
    }

    // init logging system
    Log::Init();
    NLOGD("Initializing Rwd Runtime...");

    // init input
    m_inputManager = n_uptr<InputManager>(new InputManager());
    m_inputManager->init();

    // init window
    m_window = n_uptr<WindowBase>(WindowBase::Create());
    m_window->init();

    m_initialized = true;

    return;
}

void RwdRuntime::shutdown() {
    // shutdown input system
    m_inputManager.reset();

    // close window
    m_window.reset();

    // clear logger
    Log::Clear();
}

void RwdRuntime::tick() {
    // update window
    m_window->update();

    return;
}

void RwdRuntime::flush() {
    // swap window buffer
    m_window->endFrame();
}
} // namespace Rwd