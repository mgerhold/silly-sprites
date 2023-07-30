#pragma once
namespace sly::gl {
    enum class Keys {
        KeySpace,
        KeyApostrophe,
        KeyComma,
        KeyMinus,
        KeyPeriod,
        KeySlash,
        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        KeySemicolon,
        KeyEqual,
        KeyA,
        KeyB,
        KeyC,
        KeyD,
        KeyE,
        KeyF,
        KeyG,
        KeyH,
        KeyI,
        KeyJ,
        KeyK,
        KeyL,
        KeyM,
        KeyN,
        KeyO,
        KeyP,
        KeyQ,
        KeyR,
        KeyS,
        KeyT,
        KeyU,
        KeyV,
        KeyW,
        KeyX,
        KeyY,
        KeyZ,
        KeyLeftBracket,
        KeyBackslash,
        KeyRightBracket,
        KeyGraveAccent,
        KeyWorld1,
        KeyWorld2,
        KeyEscape,
        KeyEnter,
        KeyTab,
        KeyBackspace,
        KeyInsert,
        KeyDelete,
        KeyRight,
        KeyLeft,
        KeyDown,
        KeyUp,
        KeyPageUp,
        KeyPageDown,
        KeyHome,
        KeyEnd,
        KeyCapsLock,
        KeyScrollLock,
        KeyNumLock,
        KeyPrintScreen,
        KeyPause,
        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,
        KeyF13,
        KeyF14,
        KeyF15,
        KeyF16,
        KeyF17,
        KeyF18,
        KeyF19,
        KeyF20,
        KeyF21,
        KeyF22,
        KeyF23,
        KeyF24,
        KeyF25,
        KeyKp0,
        KeyKp1,
        KeyKp2,
        KeyKp3,
        KeyKp4,
        KeyKp5,
        KeyKp6,
        KeyKp7,
        KeyKp8,
        KeyKp9,
        KeyKpDecimal,
        KeyKpDivide,
        KeyKpMultiply,
        KeyKpSubtract,
        KeyKpAdd,
        KeyKpEnter,
        KeyKpEqual,
        KeyLeftShift,
        KeyLeftControl,
        KeyLeftAlt,
        KeyLeftSuper,
        KeyRightShift,
        KeyRightControl,
        KeyRightAlt,
        KeyRightSuper,
        KeyMenu,
    };
    [[nodiscard]] constexpr Keys glfw_to_key(int glfw) {
        switch (glfw) {
            case GLFW_KEY_Space:
                return Keys::KeySpace;
            case GLFW_KEY_Apostrophe:
                return Keys::KeyApostrophe;
            case GLFW_KEY_Comma:
                return Keys::KeyComma;
            case GLFW_KEY_Minus:
                return Keys::KeyMinus;
            case GLFW_KEY_Period:
                return Keys::KeyPeriod;
            case GLFW_KEY_Slash:
                return Keys::KeySlash;
            case GLFW_KEY_0:
                return Keys::Key0;
            case GLFW_KEY_1:
                return Keys::Key1;
            case GLFW_KEY_2:
                return Keys::Key2;
            case GLFW_KEY_3:
                return Keys::Key3;
            case GLFW_KEY_4:
                return Keys::Key4;
            case GLFW_KEY_5:
                return Keys::Key5;
            case GLFW_KEY_6:
                return Keys::Key6;
            case GLFW_KEY_7:
                return Keys::Key7;
            case GLFW_KEY_8:
                return Keys::Key8;
            case GLFW_KEY_9:
                return Keys::Key9;
            case GLFW_KEY_Semicolon:
                return Keys::KeySemicolon;
            case GLFW_KEY_Equal:
                return Keys::KeyEqual;
            case GLFW_KEY_A:
                return Keys::KeyA;
            case GLFW_KEY_B:
                return Keys::KeyB;
            case GLFW_KEY_C:
                return Keys::KeyC;
            case GLFW_KEY_D:
                return Keys::KeyD;
            case GLFW_KEY_E:
                return Keys::KeyE;
            case GLFW_KEY_F:
                return Keys::KeyF;
            case GLFW_KEY_G:
                return Keys::KeyG;
            case GLFW_KEY_H:
                return Keys::KeyH;
            case GLFW_KEY_I:
                return Keys::KeyI;
            case GLFW_KEY_J:
                return Keys::KeyJ;
            case GLFW_KEY_K:
                return Keys::KeyK;
            case GLFW_KEY_L:
                return Keys::KeyL;
            case GLFW_KEY_M:
                return Keys::KeyM;
            case GLFW_KEY_N:
                return Keys::KeyN;
            case GLFW_KEY_O:
                return Keys::KeyO;
            case GLFW_KEY_P:
                return Keys::KeyP;
            case GLFW_KEY_Q:
                return Keys::KeyQ;
            case GLFW_KEY_R:
                return Keys::KeyR;
            case GLFW_KEY_S:
                return Keys::KeyS;
            case GLFW_KEY_T:
                return Keys::KeyT;
            case GLFW_KEY_U:
                return Keys::KeyU;
            case GLFW_KEY_V:
                return Keys::KeyV;
            case GLFW_KEY_W:
                return Keys::KeyW;
            case GLFW_KEY_X:
                return Keys::KeyX;
            case GLFW_KEY_Y:
                return Keys::KeyY;
            case GLFW_KEY_Z:
                return Keys::KeyZ;
            case GLFW_KEY_LeftBracket:
                return Keys::KeyLeftBracket;
            case GLFW_KEY_Backslash:
                return Keys::KeyBackslash;
            case GLFW_KEY_RightBracket:
                return Keys::KeyRightBracket;
            case GLFW_KEY_GraveAccent:
                return Keys::KeyGraveAccent;
            case GLFW_KEY_World1:
                return Keys::KeyWorld1;
            case GLFW_KEY_World2:
                return Keys::KeyWorld2;
            case GLFW_KEY_Escape:
                return Keys::KeyEscape;
            case GLFW_KEY_Enter:
                return Keys::KeyEnter;
            case GLFW_KEY_Tab:
                return Keys::KeyTab;
            case GLFW_KEY_Backspace:
                return Keys::KeyBackspace;
            case GLFW_KEY_Insert:
                return Keys::KeyInsert;
            case GLFW_KEY_Delete:
                return Keys::KeyDelete;
            case GLFW_KEY_Right:
                return Keys::KeyRight;
            case GLFW_KEY_Left:
                return Keys::KeyLeft;
            case GLFW_KEY_Down:
                return Keys::KeyDown;
            case GLFW_KEY_Up:
                return Keys::KeyUp;
            case GLFW_KEY_PageUp:
                return Keys::KeyPageUp;
            case GLFW_KEY_PageDown:
                return Keys::KeyPageDown;
            case GLFW_KEY_Home:
                return Keys::KeyHome;
            case GLFW_KEY_End:
                return Keys::KeyEnd;
            case GLFW_KEY_CapsLock:
                return Keys::KeyCapsLock;
            case GLFW_KEY_ScrollLock:
                return Keys::KeyScrollLock;
            case GLFW_KEY_NumLock:
                return Keys::KeyNumLock;
            case GLFW_KEY_PrintScreen:
                return Keys::KeyPrintScreen;
            case GLFW_KEY_Pause:
                return Keys::KeyPause;
            case GLFW_KEY_F1:
                return Keys::KeyF1;
            case GLFW_KEY_F2:
                return Keys::KeyF2;
            case GLFW_KEY_F3:
                return Keys::KeyF3;
            case GLFW_KEY_F4:
                return Keys::KeyF4;
            case GLFW_KEY_F5:
                return Keys::KeyF5;
            case GLFW_KEY_F6:
                return Keys::KeyF6;
            case GLFW_KEY_F7:
                return Keys::KeyF7;
            case GLFW_KEY_F8:
                return Keys::KeyF8;
            case GLFW_KEY_F9:
                return Keys::KeyF9;
            case GLFW_KEY_F10:
                return Keys::KeyF10;
            case GLFW_KEY_F11:
                return Keys::KeyF11;
            case GLFW_KEY_F12:
                return Keys::KeyF12;
            case GLFW_KEY_F13:
                return Keys::KeyF13;
            case GLFW_KEY_F14:
                return Keys::KeyF14;
            case GLFW_KEY_F15:
                return Keys::KeyF15;
            case GLFW_KEY_F16:
                return Keys::KeyF16;
            case GLFW_KEY_F17:
                return Keys::KeyF17;
            case GLFW_KEY_F18:
                return Keys::KeyF18;
            case GLFW_KEY_F19:
                return Keys::KeyF19;
            case GLFW_KEY_F20:
                return Keys::KeyF20;
            case GLFW_KEY_F21:
                return Keys::KeyF21;
            case GLFW_KEY_F22:
                return Keys::KeyF22;
            case GLFW_KEY_F23:
                return Keys::KeyF23;
            case GLFW_KEY_F24:
                return Keys::KeyF24;
            case GLFW_KEY_F25:
                return Keys::KeyF25;
            case GLFW_KEY_Kp0:
                return Keys::KeyKp0;
            case GLFW_KEY_Kp1:
                return Keys::KeyKp1;
            case GLFW_KEY_Kp2:
                return Keys::KeyKp2;
            case GLFW_KEY_Kp3:
                return Keys::KeyKp3;
            case GLFW_KEY_Kp4:
                return Keys::KeyKp4;
            case GLFW_KEY_Kp5:
                return Keys::KeyKp5;
            case GLFW_KEY_Kp6:
                return Keys::KeyKp6;
            case GLFW_KEY_Kp7:
                return Keys::KeyKp7;
            case GLFW_KEY_Kp8:
                return Keys::KeyKp8;
            case GLFW_KEY_Kp9:
                return Keys::KeyKp9;
            case GLFW_KEY_KpDecimal:
                return Keys::KeyKpDecimal;
            case GLFW_KEY_KpDivide:
                return Keys::KeyKpDivide;
            case GLFW_KEY_KpMultiply:
                return Keys::KeyKpMultiply;
            case GLFW_KEY_KpSubtract:
                return Keys::KeyKpSubtract;
            case GLFW_KEY_KpAdd:
                return Keys::KeyKpAdd;
            case GLFW_KEY_KpEnter:
                return Keys::KeyKpEnter;
            case GLFW_KEY_KpEqual:
                return Keys::KeyKpEqual;
            case GLFW_KEY_LeftShift:
                return Keys::KeyLeftShift;
            case GLFW_KEY_LeftControl:
                return Keys::KeyLeftControl;
            case GLFW_KEY_LeftAlt:
                return Keys::KeyLeftAlt;
            case GLFW_KEY_LeftSuper:
                return Keys::KeyLeftSuper;
            case GLFW_KEY_RightShift:
                return Keys::KeyRightShift;
            case GLFW_KEY_RightControl:
                return Keys::KeyRightControl;
            case GLFW_KEY_RightAlt:
                return Keys::KeyRightAlt;
            case GLFW_KEY_RightSuper:
                return Keys::KeyRightSuper;
            case GLFW_KEY_Menu:
                return Keys::KeyMenu;
            default:
                return assert(false);
        }
    }
} // namespace sly::gl
