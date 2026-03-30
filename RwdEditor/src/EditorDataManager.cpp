#include <pch.h>
#include "EditorDataManager.h"
#include "Core/Log/Sink/gui_sink.h"

namespace Rwd {
EditorDataManager::EditorDataManager() {
    m_logMsgs = make_shared<n_cqueue_safe<log_item>>(MAX_LOG_MSG);

    // construct ui sink for editor
    auto ui_sink = gui_sink_mt(m_logMsgs);
    EDITOR_ASSERT(ui_sink, "ConsolePanel: init failed because log container is null!");
    Log::AddSink(std::move(ui_sink));
}

EditorDataManager::~EditorDataManager() {
    m_logMsgs.reset();
}
} // namespace Rwd