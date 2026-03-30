#include <pch.h>
#include "Log.h"

namespace Rwd {
std::shared_ptr<spdlog::logger> Log::s_RuntimeLogger;
std::shared_ptr<spdlog::logger> Log::s_EditorLogger;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    // Rwd logger has console sink by default
    s_RuntimeLogger = spdlog::stdout_color_mt("Runtime");
    s_RuntimeLogger->set_level(spdlog::level::trace);

    s_EditorLogger = spdlog::stderr_color_mt("Editor");
    s_EditorLogger->set_level(spdlog::level::trace);
}

void Log::Clear() {
    s_RuntimeLogger.reset();
    s_EditorLogger.reset();
}

void Log::AddSink(log_sink &&sink) {
    auto &rtSinks = s_RuntimeLogger->sinks();
    auto &edtSinks = s_EditorLogger->sinks();

    rtSinks.emplace_back(sink);
    edtSinks.emplace_back(sink);
}

void Log::ReloadSink(char sink_mask) {
    // todo
}
} // namespace Rwd