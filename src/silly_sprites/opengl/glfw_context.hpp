#pragma once

#include "gl_error.hpp"
#include "spdlog/spdlog.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <tl/expected.hpp>

namespace sly::gl {

    class GlfwContext final {
    private:
        bool m_initialized;

        GlfwContext() : m_initialized{ true } { }

    public:
        ~GlfwContext();

        GlfwContext(const GlfwContext&) = delete;
        GlfwContext& operator=(const GlfwContext&) = delete;

        GlfwContext(GlfwContext&& other) noexcept : m_initialized{ other.m_initialized } {
            other.m_initialized = false;
        }

        GlfwContext& operator=(GlfwContext&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            std::swap(m_initialized, other.m_initialized);
            return *this;
        }

        [[nodiscard]] static tl::expected<GlfwContext, GlError> create();
    };

} // namespace sly::gl
