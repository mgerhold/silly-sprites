#include "glfw_context.hpp"

#include <spdlog/spdlog.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <tl/expected.hpp>

namespace sly::gl {

    GlfwContext::GlfwContext() {
        glfwSetErrorCallback(error_callback);
        if (glfwInit() == GLFW_FALSE) {
            spdlog::critical("Failed to initialize GLFW");
            throw GlError{ GlErrorType::FailedToInitializeGlfw };
        }
        m_initialized = true;
        spdlog::info("GLFW initialized");
    }

    GlfwContext::~GlfwContext() {
        if (m_initialized) {
            glfwTerminate();
            spdlog::info("GLFW terminated");
        }
    }

} // namespace sly::gl
