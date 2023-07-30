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
            if (Input::is_key_down(Keys::KeyA)) { spdlog::info("a is down"); }
            if (Input::is_key_up(Keys::KeyA)) { spdlog::info("a is up"); }
        }
    }
} // namespace sly::gl
