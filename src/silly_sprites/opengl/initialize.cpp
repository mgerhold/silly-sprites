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

        auto result = Input::add_close_input({ Keys::KeyEscape, Keys::KeyA });
        spdlog::info("result {}", result);
        while (not window->should_close()) {
            window->swap_buffers();
            glfwPollEvents();
            Input::update(window.value());
        }
    }
} // namespace sly::gl
