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
            Input::update_keys(window.value());
            if (Input::is_key_pressed(Keys::KeyA)) { spdlog::info("a is press"); }
            if (Input::is_key_down(Keys::KeyA)) { spdlog::info("a is down"); }
            if (Input::is_key_hold(Keys::KeyA)) { spdlog::info("a is hold"); }
            if (Input::is_key_released(Keys::KeyA)) { spdlog::info("a is release"); }
            if (Input::is_key_up(Keys::KeyA)) { spdlog::info("a is up"); }
            if (Input::is_key_raised(Keys::KeyA)) { spdlog::info("a is raise"); }
        }
    }
} // namespace sly::gl
