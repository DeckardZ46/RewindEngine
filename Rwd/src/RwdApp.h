/**
 * < Rewind Engine > RwdApp.h
 * Author: DeckardZ46
 * Date: 2024/11/13
 * Note: Rewind application base class, game & editor should both inherited from this class.
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#include <Rwd.h>

namespace Rwd{
class RwdApp {
public:
    RwdApp(std::string name = "Rwd App");
    virtual ~RwdApp();

    virtual void update();
    virtual void flush();

protected:
    std::string m_name;
};
} // namespace Rwd