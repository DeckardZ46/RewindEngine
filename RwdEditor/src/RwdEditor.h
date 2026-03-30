/**
 * < Rewind Engine > RwdEditor.h
 * Author: DeckardZ46
 * Date: 2024/09/09
 * Note: RwdEditor class header file
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#include <RwdApp.h>
#include "GUI/EditorUI.h"

namespace Rwd {
class RwdEditor : public RwdApp {
  public:
    RwdEditor();
    ~RwdEditor();

    void init();
    void close();
    void update() override;

  private:
    RUniquePtr<EditorUI> m_GUI;
};
} // namespace Rwd