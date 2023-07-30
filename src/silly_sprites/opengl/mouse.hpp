#pragma once
namespace sly::gl {
    enum class Mouse {
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        KeyLeft = Key1,
        KeyRight = Key2,
        KeyMiddle = Key3,
    };
    [[nodiscard]] constexpr Mouse glfw_to_mouse(int glfw) {
        switch (glfw) {
            case GLFW_MOUSE_BUTTON_1:
                return Mouse::Key1;
            case GLFW_MOUSE_BUTTON_2:
                return Mouse::Key2;
            case GLFW_MOUSE_BUTTON_3:
                return Mouse::Key3;
            case GLFW_MOUSE_BUTTON_4:
                return Mouse::Key4;
            case GLFW_MOUSE_BUTTON_5:
                return Mouse::Key5;
            case GLFW_MOUSE_BUTTON_6:
                return Mouse::Key6;
            case GLFW_MOUSE_BUTTON_7:
                return Mouse::Key7;
            case GLFW_MOUSE_BUTTON_8:
                return Mouse::Key8;
            default:
                assert(false);
                throw std::runtime_error("invalid glfw mouse define");
        }
    }
    [[nodiscard]] constexpr int mouse_to_glfw(Mouse key) {
        switch (key) {
            case Mouse::Key1:
                return GLFW_MOUSE_BUTTON_1;
            case Mouse::Key2:
                return GLFW_MOUSE_BUTTON_2;
            case Mouse::Key3:
                return GLFW_MOUSE_BUTTON_3;
            case Mouse::Key4:
                return GLFW_MOUSE_BUTTON_4;
            case Mouse::Key5:
                return GLFW_MOUSE_BUTTON_5;
            case Mouse::Key6:
                return GLFW_MOUSE_BUTTON_6;
            case Mouse::Key7:
                return GLFW_MOUSE_BUTTON_7;
            case Mouse::Key8:
                return GLFW_MOUSE_BUTTON_8;
            default:
                assert(false);
                throw std::runtime_error("invalid mouse enum");
        }
    }
} // namespace sly::gl
