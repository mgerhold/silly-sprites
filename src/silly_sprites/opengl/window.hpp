#pragma once

#define GLFW_INCLUDE_NONE
#include "error.hpp"
#include "glfw_context.hpp"
#include <memory>


namespace sly {
    class Input;
}

struct GLFWwindow;

namespace sly::gl {

    class Window final {
    private:
        friend class ::sly::Input;
        GlfwContext m_context;

        using Deleter = void (*)(GLFWwindow*);
        std::unique_ptr<GLFWwindow, Deleter> m_window;

        [[nodiscard]] GLFWwindow* get() const;

        [[nodiscard]] std::unique_ptr<GLFWwindow, Deleter> create(int width, int height);

    public:
        Window(int width, int height);

        [[nodiscard]] bool should_close() const;

        void swap_buffers();

        void poll() const;
    };
} // namespace sly::gl
