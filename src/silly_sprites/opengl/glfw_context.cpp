#include "glfw_context.hpp"

namespace sly::gl {

    GlfwContext::~GlfwContext() {
        if (m_initialized) {
            glfwTerminate();
            spdlog::info("GLFW terminated");
        }
    }

    [[nodiscard]] tl::expected<GlfwContext, GlError> GlfwContext::create() {
        glfwSetErrorCallback(error_callback);
        if (glfwInit() == GLFW_FALSE) {
            spdlog::critical("Failed to initialize GLFW");
            return tl::unexpected{ GlError::FailedToInitializeGlfw };
        }
        spdlog::info("GLFW initialized");
        return GlfwContext{};
    }

} // namespace sly::gl
