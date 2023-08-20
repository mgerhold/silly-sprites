#pragma once

#include "class_info.hpp"
#include <cassert>

class asIScriptModule;

namespace sly::script {

    class Module final {
    private:
        asIScriptModule* m_module;

        explicit Module(asIScriptModule* module) : m_module{ module } {
            assert(m_module != nullptr);
        }

        friend class Engine;

    public:
        Module(Module const&) = delete;
        Module(Module&& other) noexcept;
        Module& operator=(Module const&) = delete;
        Module& operator=(Module&& other) noexcept;
        ~Module();

        [[nodiscard]] ClassInfoRange classes() const {
            return ClassInfoRange{ m_module };
        }
    };

} // namespace sly::script
