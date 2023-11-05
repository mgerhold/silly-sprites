#include "event_system.hpp"

namespace sly {
    class Global final {
    private:
        event::EventSystem m_event_system;

    public:
        Global() = default;
        Global(Global const&) = delete;
        Global(Global&&) = delete;
        Global& operator=(Global const&) = delete;
        Global& operator=(Global&&) = delete;

        [[nodiscard]] static Global& get() {
            static auto app_context = Global{};
            return app_context;
        }

        [[nodiscard]] event::EventSystem const& event_system() const {
            return m_event_system;
        }

        [[nodiscard]] event::EventSystem& event_system() {
            return m_event_system;
        }
    };
} // namespace sly
