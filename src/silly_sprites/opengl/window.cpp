#include "window.hpp"
#include <glad/gl.h>

namespace sly::gl {

    namespace {
        void destroy_glfw_window(GLFWwindow* const window) {
            glfwDestroyWindow(window);
            spdlog::info("window destroyed");
        }

        void on_framebuffer_size_changed([[maybe_unused]] GLFWwindow* const window, int const width, int const height) {
            glViewport(0, 0, width, height);
        }
    } // namespace

    Window::Window(GlfwContext context, GLFWwindow* window)
        : m_context{ std::move(context) },
          m_window{ window, destroy_glfw_window } { }

    [[nodiscard]] GLFWwindow* Window::get() const {
        return m_window.get();
    }

    [[nodiscard]] Window Window::create(int const width, int const height) {
        auto context = GlfwContext::create();
        if (not context.has_value()) {
            spdlog::critical("Unable to create GLFW context");
            throw GlError{ GlErrorType::UnableToCreateGlfwContext };
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* const window = glfwCreateWindow(width, height, "coder2k bester Mann", nullptr, nullptr);
        if (window == nullptr) {
            spdlog::critical("Failed to create GLFW window");
            throw GlError{ GlErrorType::FailedToCreateWindow };
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
        glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

        if (not gladLoadGL(glfwGetProcAddress)) {
            spdlog::critical("Failed to initialize Glad");
            throw GlError{ GlErrorType::FailedToInitializeGlad };
        }

        gl::on_framebuffer_size_changed(window, width, height);  // addressing the gl namespace becuase otherwise the function is ambiguous
        glfwSetFramebufferSizeCallback(window, gl::on_framebuffer_size_changed);

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
