#include <pch.h>
#include <RwdApp.h>

namespace Rwd{
RwdApp::RwdApp(string name): m_name(name){
    // init runtime
    RwdRuntime::Get();
}

RwdApp::~RwdApp(){
    // close runtime
    RwdRuntime::Get().shutdown();
}

void RwdApp::update(){
    // runtime tick logic & render
    RwdRuntime::Get().tick();
}

void RwdApp::flush(){
    // swap window buffer
    RwdRuntime::Get().flush();
}
} // namespace Rwd