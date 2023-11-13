#include "events.hpp"
#include "types.hpp"
#include <tl/optional.hpp>
#include <unordered_map>
#include <cassert>

namespace sly::event {

    struct EvenHandlerId final {
        friend class EventSystem;
        friend struct std::hash<EvenHandlerId>;

    private:
        tl::optional<usize> m_id;
        constexpr EvenHandlerId(usize id) : m_id{ id } { }

    public:
        constexpr EvenHandlerId() : m_id{ tl::nullopt } { }
        [[nodiscard]] constexpr auto operator<=>(EvenHandlerId const&) const = default;
    };
}

template<>
struct std::hash<sly::event::EvenHandlerId> {
    std::size_t operator()(sly::event::EvenHandlerId const& id) const {
        assert(id.m_id.has_value());
        return std::hash<size_t>()(id.m_id.value());
    }
};

namespace sly::event {
    class EventSystem final {
    private:
        std::unordered_map<EvenHandlerId, EventCallbacks> m_handlers;
        usize m_event_id = 0;

        template<Event T>
        [[nodiscard]] static bool
        is_same_handler(std::function<void(T const&)> const& handler, std::function<void(T const&)> const& handler2) {
            return handler == handler2;
        }

    public:
        EventSystem() = default;
        EventSystem(EventSystem const&) = delete;
        EventSystem(EventSystem&&) = delete;
        EventSystem& operator=(EventSystem const&) = delete;
        EventSystem& operator=(EventSystem&&) = delete;

        template<Event T>
        EvenHandlerId add_handler(std::function<void(T const&)> handler) {
            auto const id = EvenHandlerId{ m_event_id++ };
            m_handlers[id] = handler;
            return id;
        }

        void remove_handler(EvenHandlerId id);

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
