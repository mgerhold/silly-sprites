#include "../silly_sprites/input.hpp"
#include "../silly_sprites/opengl/window.hpp"
#include "magic_enum_wrapper.hpp"

int main() {
    auto window = sly::gl::Window::create(800, 600);

    if (not window.has_value()) {
        spdlog::critical(magic_enum::enum_name(window.error()));
        return 0;
    }

    while (not window->should_close()) {
        window->swap_buffers();
        glfwPollEvents();
        sly::Input::update(window.value());
    }
}
