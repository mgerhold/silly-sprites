#pragma once

#include <angelscript.h>
#include <cassert>
#include <utility>

namespace sly::script {

    class TypeInfo final {
    private:
        asITypeInfo* m_type_info{ nullptr };

        TypeInfo() = default;

        explicit TypeInfo(asITypeInfo* const type_info) : m_type_info{ type_info } {
            assert(m_type_info != nullptr);
            m_type_info->AddRef();
        }

    public:
        TypeInfo(TypeInfo const& other) : m_type_info{ other.m_type_info } {
            m_type_info->AddRef();
        }

        TypeInfo(TypeInfo&& other) noexcept : m_type_info{ std::exchange(other.m_type_info, nullptr) } { }

        TypeInfo& operator=(TypeInfo const& other) {
            if (this == &other) {
                return *this;
            }

            if (m_type_info != nullptr) {
                m_type_info->Release();
            }

            m_type_info = other.m_type_info;
            if (m_type_info != nullptr) {
                m_type_info->AddRef();
            }

            return *this;
        }

        TypeInfo& operator=(TypeInfo&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            std::swap(m_type_info, other.m_type_info);
            return *this;
        }

        ~TypeInfo() {
            if (m_type_info != nullptr) {
                m_type_info->Release();
                m_type_info = nullptr;
            }
        }

        friend class Engine;
    };

} // namespace sly::script
