#include "glfw_context.hpp"

namespace sly::gl {

    GlfwContext::~GlfwContext() {
        glfwTerminate();
    }

    [[nodiscard]] tl::expected<GlfwContext, GlError> GlfwContext::create() {
        auto const result{ glfwInit() };
        if (result == GLFW_FALSE) {
            spdlog::critical("Failed to initialize GLFW");
            return tl::unexpected{ GlError::FailedToInitializeGlfw };
        }
        return GlfwContext{};
    }

} // namespace sly::gl
