/** 
 * < Rewind Engine > Entry.cpp
 * Author: DeckardZ46
 * Date: 2024/07/10
 * Note: This is entry point of Rewind Engine Editor
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */

// Platform specific settings
#ifdef Rwd_PLAT_WINDOWS
    #include <Windows.h>
#endif

#include <pch.h>
#include "RwdEditor.h"

int main() {
#ifdef Rwd_PLAT_WINDOWS
    FreeConsole();
#endif
    Rwd::RwdEditor editor;
    editor.init();
    while (!Rwd::RwdRuntime::Get().getWindow().isClose()) {
        editor.update();
    }
    editor.close();
}