#pragma once
#include <GLFW/glfw3.h>
#include <cassert>
#include <stdexcept>
namespace sly::gl {
    enum class MouseButton {
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
    [[nodiscard]] constexpr MouseButton glfw_to_mouse(int glfw) {
        switch (glfw) {
            case GLFW_MOUSE_BUTTON_1:
                return MouseButton::Button1;
            case GLFW_MOUSE_BUTTON_2:
                return MouseButton::Button2;
            case GLFW_MOUSE_BUTTON_3:
                return MouseButton::Button3;
            case GLFW_MOUSE_BUTTON_4:
                return MouseButton::Button4;
            case GLFW_MOUSE_BUTTON_5:
                return MouseButton::Button5;
            case GLFW_MOUSE_BUTTON_6:
                return MouseButton::Button6;
            case GLFW_MOUSE_BUTTON_7:
                return MouseButton::Button7;
            case GLFW_MOUSE_BUTTON_8:
                return MouseButton::Button8;
            default:
                assert(false);
                throw std::runtime_error("invalid glfw mouse define");
        }
    }
    [[nodiscard]] constexpr int mouse_to_glfw(MouseButton key) {
        switch (key) {
            case MouseButton::Button1:
                return GLFW_MOUSE_BUTTON_1;
            case MouseButton::Button2:
                return GLFW_MOUSE_BUTTON_2;
            case MouseButton::Button3:
                return GLFW_MOUSE_BUTTON_3;
            case MouseButton::Button4:
                return GLFW_MOUSE_BUTTON_4;
            case MouseButton::Button5:
                return GLFW_MOUSE_BUTTON_5;
            case MouseButton::Button6:
                return GLFW_MOUSE_BUTTON_6;
            case MouseButton::Button7:
                return GLFW_MOUSE_BUTTON_7;
            case MouseButton::Button8:
                return GLFW_MOUSE_BUTTON_8;
            default:
                assert(false);
                throw std::runtime_error("invalid mouse enum");
        }
    }
} // namespace sly::gl
