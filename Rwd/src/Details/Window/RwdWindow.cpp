#include <pch.h>
#include <Details/Window/RwdWindow.h>
#include <Platform/Window/Windows/WindowsWIndow.h>

namespace Rwd{
    WindowBase* WindowBase::Create(const WindowData& wdata){
#ifdef Rwd_PLAT_WINDOWS
        return new WindowsWindow(wdata);
#else
    #error Unsupported Platform!
#endif
        return nullptr;
    }
}