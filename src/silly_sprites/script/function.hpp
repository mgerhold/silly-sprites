#pragma once

#include <angelscript.h>

namespace sly::script {

    class Function final {
    private:
        asIScriptFunction* m_function;

        explicit Function(asIScriptFunction* function) : m_function{ function } { }

        friend class Engine;
    };

} // namespace sly::script
