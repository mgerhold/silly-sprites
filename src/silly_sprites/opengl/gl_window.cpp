#include "gl_window.hpp"
#include <glad/gl.h>

namespace sly::gl {

    Window::Window(GLFWwindow* window) 
        : m_window{ window } { }

    Window::~Window() {
        glfwTerminate();
        glfwDestroyWindow(m_window);
        spdlog::info("window destroyed");
    }

    [[nodiscard]] tl::expected<Window, WindowError> Window::create(int const width, int const height) {
		auto const result{ glfwInit() };
        if (result == GLFW_FALSE) {
            spdlog::critical("Failed to initialize GLFW");
            return tl::unexpected(WindowError{ "Failed to initialize GLFW" });
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(width, height, "coder2k bester Mann", nullptr, nullptr);
        if (not window) {
            spdlog::critical("Failed to create GLFW window");
            glfwTerminate();
            return tl::unexpected(WindowError{ "Failed to create GLFW window" });
        }
        glfwMakeContextCurrent(window);

        if (not gladLoadGL(glfwGetProcAddress)) {
            spdlog::critical("Failed to initialize GLSD");
            return tl::unexpected( WindowError{ "Failed to initialize GLSD" });
        }

        auto const callback{[](GLFWwindow* window, int width, int height){
            glViewport(0, 0, width, height);
        }};

        callback(window, width, height);
        glfwSetFramebufferSizeCallback(window, callback);

        spdlog::info("window initialized");

        return window ;
    }

   [[nodiscard]] GLFWwindow* Window::get() const {
        return m_window;
    }
}
