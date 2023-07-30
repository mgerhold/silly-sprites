#include "gl_initialize.hpp"
#include "window.hpp"
#include "input.h"
#include <magic_enum_wrapper.hpp>

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
            auto const mouse = Input::get_mouse_position();
            spdlog::info("mouse position -> {} | {}", mouse.first, mouse.second);
        }
    }
} // namespace sly::gl
