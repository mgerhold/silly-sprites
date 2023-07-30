#include "input.h"

namespace sly::gl {
    void Input::update_keys(Window const& window) {
    
        std::swap(current_keys, last_keys);
        current_keys.fill(false);
    
        for (int i = 0; i <= current_keys.size(); ++i) {
            auto const key = static_cast<Keys>(i);
            auto const g_key = glfwGetKey(window.get(), key_to_glfw(key));
            if (g_key == GLFW_PRESS) { current_keys[i] = true; }
            }
    }

    bool Input::is_key_down(Keys key) {
        return current_keys[static_cast<int>(key)];
    }
    bool Input::is_key_up(Keys key) {
        return not current_keys[static_cast<int>(key)];;
    }

    bool Input::is_key_pressed(Keys key) {
            return not last_keys[static_cast<int>(key)] and current_keys[static_cast<int>(key)];
    }
    bool Input::is_key_released(Keys key) {
            return last_keys[static_cast<int>(key)] and not current_keys[static_cast<int>(key)];
    }

    bool Input::is_key_hold(Keys key) {
            return last_keys[static_cast<int>(key)] and current_keys[static_cast<int>(key)];
    }
    bool Input::is_key_raised(Keys key) {
        return not last_keys[static_cast<int>(key)] and not current_keys[static_cast<int>(key)];
    }
}
