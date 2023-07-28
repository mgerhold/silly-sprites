#include "gl_window.hpp"
#include <glad/gl.h>

namespace sly::gl {

    namespace {
        void destroy_glfw_window(GLFWwindow* const window) {
            glfwDestroyWindow(window);
            spdlog::info("window destroyed");
        }
    }

    Window::Window(GlfwContext context, GLFWwindow* window)
        : m_context{ std::move(context) },
          m_window{ window, destroy_glfw_window } { }

    [[nodiscard]] GLFWwindow* Window::get() const {
        return m_window.get();
    }

    [[nodiscard]] tl::expected<Window, GlError> Window::create(int const width, int const height) {
        auto context = GlfwContext::create();
        if (not context.has_value()) {
            spdlog::critical("Unable to create GLFW context");
            return tl::unexpected{ GlError::UnableToCreateGlfwContext };
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* const window = glfwCreateWindow(width, height, "coder2k bester Mann", nullptr, nullptr);
        if (window == nullptr) {
            spdlog::critical("Failed to create GLFW window");
            return tl::unexpected{ GlError::FailedToCreateWindow };
        }
        glfwMakeContextCurrent(window);

        if (not gladLoadGL(glfwGetProcAddress)) {
            spdlog::critical("Failed to initialize Glad");
            return tl::unexpected{ GlError::FailedToInitializeGlad };
        }

        auto const callback{ [](GLFWwindow* const window, int const width, int const height) {
            glViewport(0, 0, width, height);
        } };

        callback(window, width, height);
        glfwSetFramebufferSizeCallback(window, callback);

        spdlog::info("window initialized");
        return Window{ *std::move(context), window };
    }

    bool Window::should_close() const {
        return glfwWindowShouldClose(get());
    }

    void Window::swap_buffers() {
        glfwSwapBuffers(get());
    }
} // namespace sly::gl
