#include "events.hpp"
#include "types.hpp"
#include <vector>

namespace sly::event {

    struct EventID final {
        friend class EventSystem;

    private:
        usize m_id;
        constexpr EventID(usize id) : m_id{ id } {}

    public:
        constexpr EventID() : m_id{ 0 } {}
        [[nodiscard]] constexpr auto operator<=>(EventID const&) const = default;
    };

    class EventSystem final {
    private:
        std::vector<std::pair<EventID, EventCallbacks>> m_handlers;
        usize eventID = 0;

        template<Event T>
        [[nodiscard]] bool
        is_same_handler(std::function<void(T const&)> handler, std::function<void(T const&)> handler2) {
            return handler == handler2;
        }

    public:
        EventSystem() = default;
        EventSystem(EventSystem const&) = delete;
        EventSystem(EventSystem&&) = delete;
        EventSystem& operator=(EventSystem const&) = delete;
        EventSystem& operator=(EventSystem&&) = delete;

        template<Event T>
        EventID add_handler(std::function<void(T const&)> handler) {
            auto const id = EventID{ eventID++ };
            m_handlers.push_back({ id, handler });
            return id;
        }

        void remove_handler(EventID id) {
            std::erase_if(m_handlers, [id](auto const& entry) {
                auto const& [id_, handler] = entry;
                return id_ == id;
            });
        }


        template<Event T>
        void dispatch(T const& event) const {
            for (auto const& [id, handler] : m_handlers) {
                std::visit(
                        [&event](auto&& handler) {
                            if constexpr (requires() { handler(event); }) {
                                handler(event);
                            }
                        },
                        handler
                );
            }
        }
    };

} // namespace sly::event
