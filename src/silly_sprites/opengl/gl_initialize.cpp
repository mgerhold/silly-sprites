#include <tl/expected.hpp>
#include "gl_initialize.hpp"
#include "gl_window.hpp"
#include "gl_error.hpp"

namespace sly::gl {

    void initialize(int const width, int const height) {
        spdlog::info("before window");

        auto window = Window::create(width, height);

        if (not window.has_value()) {
            spdlog::critical(window.error().get_message());
            return;
        }

        spdlog::info("before loop");

        while (not glfwWindowShouldClose(window->get())) {
            glfwSwapBuffers(window->get());
            glfwPollEvents();
        }
        spdlog::info("after loop");
    }

} // namespace sly::gl