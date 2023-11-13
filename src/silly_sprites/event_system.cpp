#include "event_system.hpp"
#include "app_context.hpp"

namespace sly::event {
    EventHandlerId::EventHandlerId(EventHandlerId&& other) noexcept
        : m_id{ std::exchange(other.m_id, tl::nullopt) },
          m_app_context{ std::exchange(other.m_app_context, nullptr) } { }

    EventHandlerId& EventHandlerId::operator=(EventHandlerId&& other) noexcept {;
        std::swap(m_id, other.m_id);
        std::swap(m_app_context, other.m_app_context);
        return *this;
    }

    EventHandlerId::~EventHandlerId() {
        if (not m_app_context) {
            return;
        }
        m_app_context->event_system().remove_handler(*this);
    }

    EventSystem::EventSystem(AppContext* app_context) : m_app_context{ app_context } {
        // don't use the AppContext*. the object is not fully created yet.
    }

    void EventSystem::remove_handler(EventHandlerId const&  id) {
        if (not id.m_id.has_value()) {
            return;
        }

        m_handlers.erase(id.m_id.value());
    }
} // namespace sly::event
