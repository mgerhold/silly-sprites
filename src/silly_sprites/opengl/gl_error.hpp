#pragma once

#include "spdlog/spdlog.h"
#include <string>

namespace sly::gl {

    enum class GlError {
        FailedToInitializeGlfw,
        UnableToCreateGlfwContext,
        FailedToCreateWindow,
        FailedToInitializeGlad,
    };

    inline void error_callback(int code, const char* message) {
        spdlog::critical("GLFW error ({}): {}", code, message);
    }

} // namespace sly::gl
