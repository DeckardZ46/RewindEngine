/**
 * < Rewind Engine > gui_sink.h
 * Author: DeckardZ46
 * Date: 2024/09/24
 * Note: gui sink for Rewind Logger, making NLOGX print on Rewind Editor console panel
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once
#include <chrono>

#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

#include <Core/Types.h>

namespace Rwd {

struct log_item {
    bool isCmd = false;
    string msg;
    string logger;
    spdlog::log_clock::time_point time;
    spdlog::level::level_enum level;
};

template <typename Mutex> class gui_sink : public spdlog::sinks::base_sink<Mutex> {
  public:
    gui_sink(n_sptr<n_cqueue<log_item>> msg_queue) {
        messages = std::move(msg_queue);
    }

    void set_max_shown_messages(size_t max) {
        max_msg = max;
    }

  protected:
    void sink_it_(const spdlog::details::log_msg &msg) override {
        // sink_it_ is thread-safe, no more lock & unlock operation needed
        // see spdlog/sinks/base_sink-inl.h
        if (messages->isFull()) {
            messages->dequeue();
        }
        log_item it;
        it.msg = string(msg.payload.data(), msg.payload.size());
        it.logger = string(msg.logger_name.data(), msg.logger_name.size());
        it.level = msg.level;
        it.time = msg.time;
        messages->forceEnqueue(std::move(it));
    }
    void flush_() override {
        // since we directly push log items into target container, we don't need to flush it
    }

  private:
    uint16_t max_msg = MAX_LOG_MSG;
    n_sptr<n_cqueue<log_item>> messages;
};

typedef n_sptr<gui_sink<std::mutex>> gui_sink_mt_t;

inline const gui_sink_mt_t gui_sink_mt(n_sptr<n_cqueue<log_item>> target) {
    return std::make_shared<gui_sink<std::mutex>>(std::move(target));
}

} // namespace Rwd