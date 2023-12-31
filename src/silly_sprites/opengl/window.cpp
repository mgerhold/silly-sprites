#include "window.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>
#include <tl/expected.hpp>

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

    [[nodiscard]] GLFWwindow* Window::get() const {
        return m_window.get();
    }

    std::unique_ptr<GLFWwindow, Window::Deleter> Window::create(int const width, int const height) {
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

        on_framebuffer_size_changed(window, width, height);
        glfwSetFramebufferSizeCallback(window, on_framebuffer_size_changed);

        spdlog::info("window initialized");
        return { window, destroy_glfw_window };
    }

    Window::Window(int const width, int const height) : m_window{ create(width, height) } { }

    bool Window::should_close() const {
        return glfwWindowShouldClose(get());
    }

    void Window::swap_buffers() {
        glfwSwapBuffers(get());
    }

    void Window::poll() const {
        glfwPollEvents();
    }
} // namespace sly::gl
