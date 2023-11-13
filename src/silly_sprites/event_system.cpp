#include "event_system.hpp"

namespace sly::event {
    void EventSystem::remove_handler(EvenHandlerId id) {
        if (not id.m_id.has_value()) {
            spdlog::warn("tried to remove event handler id without value");
            return;
        }

        m_handlers.erase(id);
    }
} // namespace sly::event
