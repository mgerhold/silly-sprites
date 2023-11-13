#include "event_system.hpp"

namespace sly::event {
    void EventSystem::remove_handler(EvenHandlerId id) {
        if (not id.m_id.has_value()) {
            spdlog::warn("tried to remove event handler id without value");
            return;
        }
        std::erase_if(m_handlers, [id](auto const& entry) {
            auto const& [id_, unused] = entry;
            if (not id_.m_id.has_value()) {
                return false;
            }
            return id_ == id;
        });
    }
} // namespace sly::event
