#include "events.hpp"
#include "types.hpp"
#include <cassert>
#include <tl/optional.hpp>
#include <unordered_map>

namespace sly {
    class AppContext;
}

namespace sly::event {

    struct EventHandlerId final {
        friend class EventSystem;
        friend struct std::hash<EventHandlerId>;

    private:
        tl::optional<usize> m_id;
        AppContext* m_app_context;

        constexpr EventHandlerId(usize id, AppContext* app_context) : m_id{ id }, m_app_context{ app_context } { }

    public:
        constexpr EventHandlerId() : m_id{ tl::nullopt }, m_app_context{ nullptr } { }
        EventHandlerId(EventHandlerId const& other) = delete;
        EventHandlerId(EventHandlerId&& other) noexcept;
        EventHandlerId& operator=(EventHandlerId const& other) = delete;
        EventHandlerId& operator=(EventHandlerId&& other) noexcept;
        ~EventHandlerId();

        void remove();

        [[nodiscard]] constexpr auto operator<=>(EventHandlerId const&) const = default;
    };
} // namespace sly::event

template<>
struct std::hash<sly::event::EventHandlerId> final {
    [[nodiscard]] std::size_t operator()(sly::event::EventHandlerId const& id) const {
        assert(id.m_id.has_value());
        return std::hash<size_t>()(id.m_id.value());
    }
};

namespace sly::event {
    class EventSystem final {
    private:
        std::unordered_map<usize, EventCallbacks> m_handlers;
        usize m_event_id = 0;
        AppContext* m_app_context;

        template<Event T>
        [[nodiscard]] static bool
        is_same_handler(std::function<void(T const&)> const& handler, std::function<void(T const&)> const& handler2) {
            return handler == handler2;
        }

    public:
        EventSystem(AppContext* app_context);
        EventSystem(EventSystem const&) = delete;
        EventSystem(EventSystem&&) = delete;
        EventSystem& operator=(EventSystem const&) = delete;
        EventSystem& operator=(EventSystem&&) = delete;

        template<Event T>
        [[nodiscard]] EventHandlerId add_handler(std::function<void(T const&)> handler) {
            auto id = EventHandlerId{ m_event_id++, m_app_context };
            m_handlers[id.m_id.value()] = handler;
            return id;
        }

        void remove_handler(EventHandlerId const& id);

        template<Event T>
        void dispatch(T const& event) const {
            for (auto const& [unused, handler] : m_handlers) {
                std::visit(
                        [&event](auto&& dler) {
                            if constexpr (requires() { dler(event); }) {
                                dler(event);
                            }
                        },
                        handler
                );
            }
        }
    };

} // namespace sly::event
