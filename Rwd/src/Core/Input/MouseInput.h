/**
 * < Rewind Engine > MouseInput.h
 * Author: DeckardZ46
 * Date: 2025/09/01
 * Note: Mouse Input Definitions of Rewind Engine
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

#define MAX_MOUSEBUTTON_COUNT 8

namespace Rwd {
enum class RwdMouseButton : uint8 {
    AnyMouseButton  = 0,
    Left            = 1,
    Right           = 2,
    Middle          = 3,
    ButtonX1        = 4,
    ButtonX2        = 5
};

enum class RwdMouseAction : uint8 {
    None        = 0,
    Press       = 1,
    Release     = 2,
    Repeat      = 3,
    Move        = 4,
    Scroll      = 5
};
} // namespace Rwd