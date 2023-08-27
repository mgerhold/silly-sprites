#pragma once

#include "type_info.hpp"
#include <angelscript.h>

namespace sly::script {

    class Object final {
    private:
        void* m_object;
        TypeInfo m_type;

        explicit Object(void* object, TypeInfo type) : m_object{ object }, m_type{ std::move(type) } { }

        friend class Engine;
    };

} // namespace sly::script
