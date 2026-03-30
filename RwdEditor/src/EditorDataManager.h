/**
 * < Rewind Engine > EditorDataManager.h
 * Author: DeckardZ46
 * Date: 2024/09/24
 * Note: Data manager for Rewind Engine Editor, transferring data between Editor & Runtime
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

namespace Rwd {
struct log_item;
class EditorDataManager {
  private:
    EditorDataManager();
    EditorDataManager(const EditorDataManager &) = delete;
    EditorDataManager(EditorDataManager &&) = delete;
    EditorDataManager &operator=(const EditorDataManager &) = delete;
    EditorDataManager &operator=(EditorDataManager &&) = delete;

  public:
    ~EditorDataManager();

    inline static EditorDataManager &Get() {
        static EditorDataManager s_Instance;
        return s_Instance;
    }

    inline n_sptr<n_cqueue<log_item>> getLogContainer() const {
        return m_logMsgs;
    }

  private:
    n_sptr<n_cqueue_safe<log_item>> m_logMsgs;
};
} // namespace Rwd