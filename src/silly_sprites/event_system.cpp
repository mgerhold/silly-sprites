#include "event_system.hpp"
#include "app_context.hpp"

namespace sly::event {
    EventHandlerId::EventHandlerId(EventHandlerId&& other) noexcept
        : m_id{ std::exchange(other.m_id, tl::nullopt) },
          m_app_context{ std::exchange(other.m_app_context, nullptr) } { }

    EventHandlerId& EventHandlerId::operator=(EventHandlerId&& other) noexcept {
        std::swap(m_id, other.m_id);
        std::swap(m_app_context, other.m_app_context);
        return *this;
    }

    EventHandlerId::~EventHandlerId() {
        remove();
    }

    void EventHandlerId::remove() {
        if (m_app_context) {
            m_app_context->event_system().remove_handler(*this);
        }
        m_app_context = nullptr;
        m_id = tl::nullopt;
    }

    EventSystem::EventSystem(AppContext* const app_context) : m_app_context{ app_context } {
        // don't use the AppContext*. the object is not fully created yet.
    }

    void EventSystem::remove_handler(EventHandlerId const& id) {
        if (not id.m_id.has_value()) {
            return;
        }

        switch (m_state) {
            case State::Dispatching:
                m_handlers_to_delete.push_back(id.m_id.value());
                break;
            case State::Idle:
                m_handlers.erase(id.m_id.value());
                break;
        }
    }
} // namespace sly::event
