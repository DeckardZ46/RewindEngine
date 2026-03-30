/**
 * < Rewind Engine > PanelBase.h
 * Author: DeckardZ46
 * Date: 2024/09/25
 * Note: Editor panel interface, should be implemented in various panels and used by Editor UI
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#include <Core/Types.h>

namespace Rwd {
class PanelBase {
  public:
    PanelBase(std::string &&name) : m_panelName(std::move(name)) {
    }
    virtual ~PanelBase() {
    }

    virtual void update() = 0;
    virtual void draw() = 0;

    inline float getWidth() const {
        return m_panelWidth;
    }
    inline void setWidth(float width) {
        m_panelWidth = width;
    }
    inline float getHeight() const {
        return m_panelHeight;
    }
    inline void setHeight(float height) {
        m_panelHeight = height;
    }

  protected:
    std::string m_panelName;
    float m_panelWidth;
    float m_panelHeight;
};

} // namespace Rwd