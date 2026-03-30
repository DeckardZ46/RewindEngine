#include <pch.h>
#include <Rwd.h>
#include "ConsolePanel.h"
#include "EditorDataManager.h"
#include "Core/Log/Sink/gui_sink.h"

#define LEVEL spdlog::level::level_enum

namespace Rwd {
/**
 * Utils
 */
const ImColor LVL_LOG_CLR{0.7f, 0.7f, 0.7f, 1.0f};
const ImColor LVL_DBG_CLR{0.3f, 0.9f, 0.7f, 1.0f};
const ImColor LVL_INF_CLR{0.3f, 0.6f, 0.9f, 1.0f};
const ImColor LVL_WRN_CLR{0.9f, 0.9f, 0.3f, 1.0f};
const ImColor LVL_ERR_CLR{1.0f, 0.0f, 0.0f, 1.0f};
const ImColor CMD_CLR{0.71f, 0.745f, 0.92f, 1.0f};

void ClearLog();
void AddLog();
void AddCmd(string cmd, ...);
static int TextEditCallback(ImGuiInputTextCallbackData *data);

// portable helpers
static int Stricmp(const char *s1, const char *s2) {
    int d;
    while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) {
        s1++;
        s2++;
    }
    return d;
}
static int Strnicmp(const char *s1, const char *s2, int n) {
    int d = 0;
    while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) {
        s1++;
        s2++;
        n--;
    }
    return d;
}
static char *Strdup(const char *s) {
    IM_ASSERT(s);
    size_t len = strlen(s) + 1;
    void *buf = ImGui::MemAlloc(len);
    IM_ASSERT(buf);
    return (char *)memcpy(buf, (const void *)s, len);
}
static void Strtrim(char *s) {
    char *str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ')
        str_end--;
    *str_end = 0;
}

/**
 * Console Panel Members
 */
ConsolePanel::ConsolePanel(string &&name) : PanelBase(std::move(name)) {
    ELOGD("Initializing console panel...");
    float dpiscale = RwdRuntime::Get().getWindow().getDPIScale();
    m_panelWidth = 1000.0f * dpiscale;
    m_panelHeight = 200.0f * dpiscale;
    m_windowWidth = RwdRuntime::Get().getWindow().getWidth();
    m_windowHeight = RwdRuntime::Get().getWindow().getHeight();
    memset(m_inputBuf, 0, sizeof(m_inputBuf));
}

ConsolePanel::~ConsolePanel() {
}

void ConsolePanel::update() {
    // nothing to update
}

void ConsolePanel::draw() {
    ImGui::SetNextWindowPos(ImVec2(m_windowWidth * 0.5f - m_panelWidth * 0.5f, m_windowHeight - m_panelHeight));
    ImGui::SetNextWindowSize(ImVec2(m_panelWidth, m_panelHeight));
    if (!ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }
    // ------------- clear button | copy button | filter -------------
    if (ImGui::Button("Clear")) {
        ClearLog();
    }
    ImGui::SameLine();
    bool copy_to_clipboard = ImGui::Button("Copy");
    ImGui::SameLine();
    if (ImGui::Button("Add")) {
        AddLog();
    }
    ImGui::SameLine();
    m_filter.Draw("Filter", 120);
    ImGui::Separator();
    // reserve space for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    // ------------- log container -------------
    if (ImGui::BeginChild("LogContainer", ImVec2(0, -footer_height_to_reserve), ImGuiChildFlags_NavFlattened,
                          ImGuiWindowFlags_HorizontalScrollbar)) {
        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::Selectable("Clear"))
                ClearLog();
            ImGui::EndPopup();
        }
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();

        for (auto log : *EditorDataManager::Get().getLogContainer()) {
            // message filter
            if (!m_filter.PassFilter(log.msg.c_str()))
                continue;
            // print cmd
            if (log.isCmd) {
                ImGui::TextColored(CMD_CLR, ">");
                ImGui::SameLine();
                ImGui::TextColored(CMD_CLR, "%s", log.msg.c_str());
                continue;
            }
            // print log
            switch (log.level) {
            case LEVEL::debug:
                ImGui::TextColored(LVL_DBG_CLR, "DBG");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, log.logger.c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, nformat_time(log.time, TIME_NO_DATE).c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", log.msg.c_str());
                break;
            case LEVEL::info:
                ImGui::TextColored(LVL_INF_CLR, "INF");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, log.logger.c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, nformat_time(log.time, TIME_NO_DATE).c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", log.msg.c_str());
                break;
            case LEVEL::warn:
                ImGui::TextColored(LVL_WRN_CLR, "WRN");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, log.logger.c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, nformat_time(log.time, TIME_NO_DATE).c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", log.msg.c_str());
                break;
            case LEVEL::err:
                ImGui::TextColored(LVL_ERR_CLR, "ERR");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, log.logger.c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, nformat_time(log.time, TIME_NO_DATE).c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_ERR_CLR, "%s", log.msg.c_str());
                break;
            default:
                ImGui::TextColored(LVL_LOG_CLR, "LOG");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, log.logger.c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_LOG_CLR, nformat_time(log.time, TIME_NO_DATE).c_str());
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", log.msg.c_str());
                break;
            }
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();
        if (m_scrollToBottom || (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        m_scrollToBottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();
    ImGui::Separator();
    // ------------- command-line -------------
    // input callback function
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll |
                                           ImGuiInputTextFlags_CallbackCompletion;
    if (ImGui::InputText("Input", m_inputBuf, IM_ARRAYSIZE(m_inputBuf), input_text_flags, &TextEditCallback,
                         (void *)this)) {
        char *s = m_inputBuf;
        Strtrim(s);
        if (s[0]) {
            // TODO:
            // ExecCommand(s);
            AddCmd(string(s));
        }
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

int ConsolePanel::TextEditCallbackImpl(ImGuiInputTextCallbackData *data) {

    switch (data->EventFlag) {
    case ImGuiInputTextFlags_CallbackCompletion: {
        // Locate beginning of current word
        const char *word_end = data->Buf + data->CursorPos;
        const char *word_start = word_end;
        while (word_start > data->Buf) {
            const char c = word_start[-1];
            if (c == ' ' || c == '\t' || c == ',' || c == ';')
                break;
            word_start--;
        }

        // Build a list of candidates
        ImVector<const char *> candidates;
        for (int i = 0; i < m_commands.Size; i++)
            if (Strnicmp(m_commands[i], word_start, (int)(word_end - word_start)) == 0)
                candidates.push_back(m_commands[i]);

        if (candidates.Size == 0) {
            // No match
            // TODO:
        } else if (candidates.Size == 1) {
            // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
            data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
            data->InsertChars(data->CursorPos, candidates[0]);
            data->InsertChars(data->CursorPos, " ");
        } else {
            // Multiple matches. Complete as much as we can..
            // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
            int match_len = (int)(word_end - word_start);
            for (;;) {
                int c = 0;
                bool all_candidates_matches = true;
                for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                    if (i == 0)
                        c = toupper(candidates[i][match_len]);
                    else if (c == 0 || c != toupper(candidates[i][match_len]))
                        all_candidates_matches = false;
                if (!all_candidates_matches)
                    break;
                match_len++;
            }

            if (match_len > 0) {
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
            }
        }

        break;
    }
    }
    return 0;
}

/**
 * Util Implementations
 */
void ClearLog() {
    EditorDataManager::Get().getLogContainer()->clear();
}

void AddLog() {
    ELOGI("Added default log.");
}

void AddCmd(string cmd, ...) {
    log_item it{.isCmd = true, .msg = cmd, .logger = "", .time = std::chrono::system_clock::now(), .level = LEVEL::off};
    EditorDataManager::Get().getLogContainer()->forceEnqueue(std::move(it));
}

static int TextEditCallback(ImGuiInputTextCallbackData *data) {
    ConsolePanel *console = (ConsolePanel *)data->UserData;
    return console->TextEditCallbackImpl(data);
}

} // namespace Rwd