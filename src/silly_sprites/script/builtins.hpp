#pragma once

#include "types.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>
#include <tl/optional.hpp>

namespace sly {
    class Scene;
    class GameObject;
} // namespace sly

namespace sly::script::builtins {

    struct ExecutionContext {
        GameObject* game_object;

        ExecutionContext(GameObject* game_object) : game_object{ game_object } { }
    };

    inline tl::optional<ExecutionContext> g_current_script_execution_context = tl::nullopt;

    void destroy();

    void print(std::string const& text);
    void println(std::string const& text);
    void eprint(std::string const& text);
    void eprintln(std::string const& text);

    namespace logging {
        void trace(std::string const& text);
        void debug(std::string const& text);
        void info(std::string const& text);
        void warning(std::string const& text);
        void error(std::string const& text);
        void critical(std::string const& text);
    } // namespace logging

} // namespace sly::script::builtins
