#include <tl/expected.hpp>
#include "gl_initialize.hpp"
#include "gl_window.hpp"
#include "gl_error.hpp"

namespace sly::gl {

    void initialize(int const width, int const height) {

        auto window = Window::create(width, height);

        if (not window.has_value()) {
            spdlog::critical(window.error().get_message());
            return;
        }

        while (not glfwWindowShouldClose(window->get())) {
            glfwSwapBuffers(window->get());
            glfwPollEvents();
        }

        Window::destroy();
    }

} // namespace sly::gl
