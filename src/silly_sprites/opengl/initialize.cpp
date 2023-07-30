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
            if (Input::is_mouse_pressed(Mouse::KeyLeft)) { spdlog::info("a is press"); }
            if (Input::is_mouse_down(Mouse::KeyLeft)) { spdlog::info("a is down"); }
            if (Input::is_mouse_hold(Mouse::KeyLeft)) { spdlog::info("a is hold"); }
            if (Input::is_mouse_released(Mouse::KeyLeft)) { spdlog::info("a is release"); }
            if (Input::is_mouse_up(Mouse::KeyLeft)) { spdlog::info("a is up"); }
            if (Input::is_mouse_raised(Mouse::KeyLeft)) { spdlog::info("a is raise"); }
        }
    }
} // namespace sly::gl
