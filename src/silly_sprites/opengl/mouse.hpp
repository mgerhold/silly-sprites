#pragma once
namespace sly::gl {
    enum class Mouse {
        Button1,
        Button2,
        Button3,
        Button4,
        Button5,
        Button6,
        Button7,
        Button8,
        Left = Button1,
        Right = Button2,
        Middle = Button3,
    };
    [[nodiscard]] constexpr Mouse glfw_to_mouse(int glfw) {
        switch (glfw) {
            case GLFW_MOUSE_BUTTON_1:
                return Mouse::Button1;
            case GLFW_MOUSE_BUTTON_2:
                return Mouse::Button2;
            case GLFW_MOUSE_BUTTON_3:
                return Mouse::Button3;
            case GLFW_MOUSE_BUTTON_4:
                return Mouse::Button4;
            case GLFW_MOUSE_BUTTON_5:
                return Mouse::Button5;
            case GLFW_MOUSE_BUTTON_6:
                return Mouse::Button6;
            case GLFW_MOUSE_BUTTON_7:
                return Mouse::Button7;
            case GLFW_MOUSE_BUTTON_8:
                return Mouse::Button8;
            default:
                assert(false);
                throw std::runtime_error("invalid glfw mouse define");
        }
    }
    [[nodiscard]] constexpr int mouse_to_glfw(Mouse key) {
        switch (key) {
            case Mouse::Button1:
                return GLFW_MOUSE_BUTTON_1;
            case Mouse::Button2:
                return GLFW_MOUSE_BUTTON_2;
            case Mouse::Button3:
                return GLFW_MOUSE_BUTTON_3;
            case Mouse::Button4:
                return GLFW_MOUSE_BUTTON_4;
            case Mouse::Button5:
                return GLFW_MOUSE_BUTTON_5;
            case Mouse::Button6:
                return GLFW_MOUSE_BUTTON_6;
            case Mouse::Button7:
                return GLFW_MOUSE_BUTTON_7;
            case Mouse::Button8:
                return GLFW_MOUSE_BUTTON_8;
            default:
                assert(false);
                throw std::runtime_error("invalid mouse enum");
        }
    }
} // namespace sly::gl
