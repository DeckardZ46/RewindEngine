#include <pch.h>
#include "RwdEditor.h"
#include "EditorDataManager.h"

namespace Rwd {
RwdEditor::RwdEditor() : RwdApp("Rwd Editor") {
    // RwdApp's constructor will be called
}

RwdEditor::~RwdEditor() {
    // RwdApp's destructor will be called
}

/*
   Process below are mostly order sensitive in their implementations, for example: do not init Editor-GUI before init
   Runtime Manually order-controlling is needed for now
*/
void RwdEditor::init() {
    // init data manager
    EditorDataManager::Get();

    // init Editor GUI
    m_GUI = make_unique<EditorUI>();
    m_GUI->init();
}

void RwdEditor::close() {
    // clear Editor GUI
    m_GUI->clear();
    m_GUI.reset();
}

void RwdEditor::update() {
    RwdApp::update();

    // update & draw Editor GUI
    m_GUI->update();
    m_GUI->draw();

    RwdApp::flush();
}
} // namespace Rwd