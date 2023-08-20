#include "module.hpp"

#include <angelscript.h>
#include <stdexcept>

namespace sly::script {
    Module::Module(Module&& other) noexcept : m_module{ std::exchange(other.m_module, nullptr) } { }

    Module& Module::operator=(Module&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        std::swap(m_module, other.m_module);
        return *this;
    }

    Module::~Module() {
        if (m_module != nullptr) {
            m_module->Discard();
            m_module = nullptr;
        }
    }

} // namespace sly::script
