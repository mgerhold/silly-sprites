#pragma once

#include <angelscript.h>

namespace sly::script {

    class Object final {
    private:
        void* m_object;

        explicit Object(void* object) : m_object{ object } { }

        friend class Engine;
    };

} // namespace sly::script
