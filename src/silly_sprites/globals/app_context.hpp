#include "event_system.hpp"

namespace sly {
    class AppContext final {
    private:
        event::EventSystem m_event_system;

    public:
        AppContext() = default;
        AppContext(AppContext const&) = delete;
        AppContext(AppContext&&) = delete;
        AppContext& operator=(AppContext const&) = delete;
        AppContext& operator=(AppContext&&) = delete;

        [[nodiscard]] static AppContext& get() {
            static auto app_context = AppContext{};
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
