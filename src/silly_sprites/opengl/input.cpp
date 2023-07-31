#include "input.hpp"

namespace sly::gl {
    void Input::update_keys(Window const& window) {

        std::swap(current_keys, last_keys);
        current_keys.fill(false);

        for (std::size_t i = 0; i < current_keys.size(); ++i) {
            auto const key = static_cast<Key>(i);
            auto const g_key = glfwGetKey(window.get(), key_to_glfw(key));
            if (g_key == GLFW_PRESS) {
                current_keys[i] = true;
            }
        }
    }
    void Input::update_mouse(Window const& window) {
        std::swap(current_mouse, last_mouse);
        current_mouse.fill(false);

        for (std::size_t i = 0; i < current_mouse.size(); ++i) {
            auto const key = static_cast<Mouse>(i);
            auto const g_key = glfwGetMouseButton(window.get(), mouse_to_glfw(key));
            if (g_key == GLFW_PRESS) {
                current_mouse[i] = true;
            }
        }
    }
    void Input::update_mouse_position(Window const& window) {
        double x, y;
        glfwGetCursorPos(window.get(), &x, &y);
        mouse_position = { static_cast<float>(x), static_cast<float>(y) };
    }

    void Input::update(Window const& window) {
        update_keys(window);
        update_mouse(window);
        update_mouse_position(window);
    }

    [[nodiscard]] Input::Vec2 Input::get_mouse_position() {
        return mouse_position;
    }

    [[nodiscard]] bool Input::is_key_down(Key const key) {
        return current_keys[static_cast<int>(key)];
    }
    [[nodiscard]] bool Input::is_key_up(Key const key) {
        return not current_keys[static_cast<int>(key)];
        ;
    }
    [[nodiscard]] bool Input::is_key_pressed(Key const key) {
        return not last_keys[static_cast<int>(key)] and current_keys[static_cast<int>(key)];
    }
    [[nodiscard]] bool Input::is_key_released(Key const key) {
        return last_keys[static_cast<int>(key)] and not current_keys[static_cast<int>(key)];
    }

    [[nodiscard]] bool Input::is_mouse_down(Mouse const mouse) {
        return current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_up(Mouse const mouse) {
        return not current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_pressed(Mouse const mouse) {
        return not last_mouse[static_cast<int>(mouse)] and current_mouse[static_cast<int>(mouse)];
    }
    [[nodiscard]] bool Input::is_mouse_released(Mouse const mouse) {
        return last_mouse[static_cast<int>(mouse)] and not current_mouse[static_cast<int>(mouse)];
    }

} // namespace sly::gl
