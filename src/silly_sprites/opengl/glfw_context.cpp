#include "glfw_context.hpp"

namespace sly::gl {

    GlfwContext::GlfwContext() : m_initialized{ true } {
        glfwSetErrorCallback(error_callback);
        if (glfwInit() == GLFW_FALSE) {
            spdlog::critical("Failed to initialize GLFW");
            throw GlError{ GlErrorType::FailedToInitializeGlfw };
        }
        spdlog::info("GLFW initialized");
    }

    GlfwContext::~GlfwContext() {
        if (m_initialized) {
            glfwTerminate();
            spdlog::info("GLFW terminated");
        }
    }

} // namespace sly::gl
