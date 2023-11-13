#pragma once

namespace sly {

    namespace script {
        class Engine;
    }

    namespace event {
        class EventSystem;
    }

    class AppContext {
    public:
        [[nodiscard]] virtual script::Engine& script_engine() = 0;
        [[nodiscard]] virtual script::Engine const& script_engine() const = 0;

        [[nodiscard]] virtual event::EventSystem& event_system() = 0;
        [[nodiscard]] virtual event::EventSystem const& event_system() const = 0;

        virtual ~AppContext() = default;
    };
} // namespace sly
