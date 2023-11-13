#include "events.hpp"
#include "types.hpp"
#include <tl/optional.hpp>
#include <vector>

namespace sly::event {

    struct EvenHandlerId final {
        friend class EventSystem;

    private:
        tl::optional<usize> m_id;
        constexpr EvenHandlerId(usize id) : m_id{ id } {}

    public:
        constexpr EvenHandlerId() : m_id{ tl::nullopt } {}
        [[nodiscard]] constexpr auto operator<=>(EvenHandlerId const&) const = default;
    };

    class EventSystem final {
    private:
        std::vector<std::pair<EvenHandlerId, EventCallbacks>> m_handlers;
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
            m_handlers.push_back({ id, handler });
            return id;
        }

        void remove_handler(EvenHandlerId id) {
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


        template<Event T>
        void dispatch(T const& event) const {
            for (auto const& [unused, handler] : m_handlers) {
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
