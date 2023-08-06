#include "../input/input.hpp"
#include "gl_initialize.hpp"
#include "magic_enum_wrapper.hpp"
#include "window.hpp"

namespace sly::gl {

    void initialize(int const width, int const height) {
        auto window = Window::create(width, height);

        if (not window.has_value()) {
            spdlog::critical(magic_enum::enum_name(window.error()));
            return;
        }

        while (not window->should_close()) {
            window->swap_buffers();
            glfwPollEvents();
            Input::update(window.value());
        }
    }
} // namespace sly::gl
