#include "input.hpp"
#include "opengl/window.hpp"

namespace sly {
    void Input::update_keys(gl::Window const& window) {

        std::swap(s_current_keys, s_last_keys);
        s_current_keys.fill(false);

        for (usize i = 0; i < s_current_keys.size(); ++i) {
            auto const key = static_cast<Key>(i);
            auto const glfw_key = glfwGetKey(window.get(), key_to_glfw(key));
            if (glfw_key == GLFW_PRESS) {
                s_current_keys[i] = true;
            }
        }
    }
    void Input::update_mouse(gl::Window const& window) {
        std::swap(s_current_mouse, s_last_mouse);
        s_current_mouse.fill(false);

        for (usize i = 0; i < s_current_mouse.size(); ++i) {
            auto const key = static_cast<MouseButton>(i);
            auto const glfw_key = glfwGetMouseButton(window.get(), mouse_to_glfw(key));
            if (glfw_key == GLFW_PRESS) {
                s_current_mouse[i] = true;
            }
        }
    }
    void Input::update_mouse_position(gl::Window const& window) {
        double x, y;
        glfwGetCursorPos(window.get(), &x, &y);
        s_mouse_position = { static_cast<float>(x), static_cast<float>(y) };
    }

    void Input::update(gl::Window const& window) {
        update_keys(window);
        update_mouse(window);
        update_mouse_position(window);
    }

    [[nodiscard]] Vec2 Input::get_mouse_position() {
        return s_mouse_position;
    }

    [[nodiscard]] bool Input::is_key_down(Key const key) {
        return s_current_keys[static_cast<int>(key)];
    }
    [[nodiscard]] bool Input::is_key_up(Key const key) {
        return not s_current_keys[static_cast<int>(key)];
    }
    [[nodiscard]] bool Input::is_key_pressed(Key const key) {
        return not s_last_keys[static_cast<int>(key)] and s_current_keys[static_cast<int>(key)];
    }
    [[nodiscard]] bool Input::is_key_released(Key const key) {
        return s_last_keys[static_cast<int>(key)] and not s_current_keys[static_cast<int>(key)];
    }

    [[nodiscard]] bool Input::is_mouse_down(MouseButton const mouse) {
        return s_current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_up(MouseButton const mouse) {
        return not s_current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_pressed(MouseButton const mouse) {
        return not s_last_mouse[static_cast<int>(mouse)] and s_current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_released(MouseButton const mouse) {
        return s_last_mouse[static_cast<int>(mouse)] and not s_current_mouse[static_cast<int>(mouse)];
    }

} // namespace sly
