#pragma once

#include "error.hpp"
#include <utility>

namespace sly::gl {

    class GlfwContext final {
    private:
        bool m_initialized = false;

    public:
        GlfwContext();
        ~GlfwContext();

        GlfwContext(GlfwContext const&) = delete;
        GlfwContext(GlfwContext&& other) noexcept : m_initialized{ std::exchange(other.m_initialized, false) } { }

        GlfwContext& operator=(GlfwContext const&) = delete;
        GlfwContext& operator=(GlfwContext&& other) noexcept {
            if (this == std::addressof(other)) {
                return *this;
            }

            std::swap(m_initialized, other.m_initialized);
            return *this;
        }
    };

} // namespace sly::gl
