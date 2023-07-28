#pragma once

#include "gl_error.hpp"
#include "spdlog/spdlog.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <tl/expected.hpp>

namespace sly::gl {

    class GlfwContext final {
    private:
        GlfwContext() = default;

    public:
        ~GlfwContext();

        GlfwContext(const GlfwContext&) = delete;
        GlfwContext(GlfwContext&&) = default;
        GlfwContext& operator=(const GlfwContext&) = delete;
        GlfwContext& operator=(GlfwContext&&) = default;

        [[nodiscard]] static tl::expected<GlfwContext, GlError> create();
    };

} // namespace sly::gl
