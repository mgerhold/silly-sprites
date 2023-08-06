#define GLFW_INCLUDE_NONE

#include "../silly_sprites/input.hpp"
#include "../silly_sprites/opengl/window.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>

int main() {
    auto window = sly::gl::Window::create(800, 600);

    if (not window.has_value()) {
        spdlog::critical(magic_enum::enum_name(window.error()));
        return 0;
    }

    // wrap this in some kind of rendering class
    glClearColor(0.5f, 0.0f, 1.0f, 1.0f);

    while (not window->should_close()) {
        // wrap this in some kind of rendering class
        glClear(GL_COLOR_BUFFER_BIT);

        window->swap_buffers();
        glfwPollEvents();
        sly::Input::update(window.value());
    }
}
