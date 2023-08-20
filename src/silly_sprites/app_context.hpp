#pragma once

namespace sly {

    namespace script {
        class Engine;
    }

    class AppContext {
    public:
        [[nodiscard]] virtual script::Engine& script_engine() = 0;
        [[nodiscard]] virtual script::Engine const& script_engine() const = 0;

        virtual ~AppContext() = default;
    };
} // namespace sly
