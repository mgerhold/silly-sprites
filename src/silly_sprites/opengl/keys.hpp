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
            case GLFW_KEY_SPACE:
                return Keys::KeySpace;
            case GLFW_KEY_APOSTROPHE:
                return Keys::KeyApostrophe;
            case GLFW_KEY_COMMA:
                return Keys::KeyComma;
            case GLFW_KEY_MINUS:
                return Keys::KeyMinus;
            case GLFW_KEY_PERIOD:
                return Keys::KeyPeriod;
            case GLFW_KEY_SLASH:
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
            case GLFW_KEY_SEMICOLON:
                return Keys::KeySemicolon;
            case GLFW_KEY_EQUAL:
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
            case GLFW_KEY_LEFT_BRACKET:
                return Keys::KeyLeftBracket;
            case GLFW_KEY_BACKSLASH:
                return Keys::KeyBackslash;
            case GLFW_KEY_RIGHT_BRACKET:
                return Keys::KeyRightBracket;
            case GLFW_KEY_GRAVE_ACCENT:
                return Keys::KeyGraveAccent;
            case GLFW_KEY_WORLD_1:
                return Keys::KeyWorld1;
            case GLFW_KEY_WORLD_2:
                return Keys::KeyWorld2;
            case GLFW_KEY_ESCAPE:
                return Keys::KeyEscape;
            case GLFW_KEY_ENTER:
                return Keys::KeyEnter;
            case GLFW_KEY_TAB:
                return Keys::KeyTab;
            case GLFW_KEY_BACKSPACE:
                return Keys::KeyBackspace;
            case GLFW_KEY_INSERT:
                return Keys::KeyInsert;
            case GLFW_KEY_DELETE:
                return Keys::KeyDelete;
            case GLFW_KEY_RIGHT:
                return Keys::KeyRight;
            case GLFW_KEY_LEFT:
                return Keys::KeyLeft;
            case GLFW_KEY_DOWN:
                return Keys::KeyDown;
            case GLFW_KEY_UP:
                return Keys::KeyUp;
            case GLFW_KEY_PAGE_UP:
                return Keys::KeyPageUp;
            case GLFW_KEY_PAGE_DOWN:
                return Keys::KeyPageDown;
            case GLFW_KEY_HOME:
                return Keys::KeyHome;
            case GLFW_KEY_END:
                return Keys::KeyEnd;
            case GLFW_KEY_CAPS_LOCK:
                return Keys::KeyCapsLock;
            case GLFW_KEY_SCROLL_LOCK:
                return Keys::KeyScrollLock;
            case GLFW_KEY_NUM_LOCK:
                return Keys::KeyNumLock;
            case GLFW_KEY_PRINT_SCREEN:
                return Keys::KeyPrintScreen;
            case GLFW_KEY_PAUSE:
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
            case GLFW_KEY_KP_0:
                return Keys::KeyKp0;
            case GLFW_KEY_KP_1:
                return Keys::KeyKp1;
            case GLFW_KEY_KP_2:
                return Keys::KeyKp2;
            case GLFW_KEY_KP_3:
                return Keys::KeyKp3;
            case GLFW_KEY_KP_4:
                return Keys::KeyKp4;
            case GLFW_KEY_KP_5:
                return Keys::KeyKp5;
            case GLFW_KEY_KP_6:
                return Keys::KeyKp6;
            case GLFW_KEY_KP_7:
                return Keys::KeyKp7;
            case GLFW_KEY_KP_8:
                return Keys::KeyKp8;
            case GLFW_KEY_KP_9:
                return Keys::KeyKp9;
            case GLFW_KEY_KP_DECIMAL:
                return Keys::KeyKpDecimal;
            case GLFW_KEY_KP_DIVIDE:
                return Keys::KeyKpDivide;
            case GLFW_KEY_KP_MULTIPLY:
                return Keys::KeyKpMultiply;
            case GLFW_KEY_KP_SUBTRACT:
                return Keys::KeyKpSubtract;
            case GLFW_KEY_KP_ADD:
                return Keys::KeyKpAdd;
            case GLFW_KEY_KP_ENTER:
                return Keys::KeyKpEnter;
            case GLFW_KEY_KP_EQUAL:
                return Keys::KeyKpEqual;
            case GLFW_KEY_LEFT_SHIFT:
                return Keys::KeyLeftShift;
            case GLFW_KEY_LEFT_CONTROL:
                return Keys::KeyLeftControl;
            case GLFW_KEY_LEFT_ALT:
                return Keys::KeyLeftAlt;
            case GLFW_KEY_LEFT_SUPER:
                return Keys::KeyLeftSuper;
            case GLFW_KEY_RIGHT_SHIFT:
                return Keys::KeyRightShift;
            case GLFW_KEY_RIGHT_CONTROL:
                return Keys::KeyRightControl;
            case GLFW_KEY_RIGHT_ALT:
                return Keys::KeyRightAlt;
            case GLFW_KEY_RIGHT_SUPER:
                return Keys::KeyRightSuper;
            case GLFW_KEY_MENU:
                return Keys::KeyMenu;
            default:
                assert(false);
                throw std::runtime_error("invalid glfw key define");
        }
    }
    [[nodiscard]] constexpr int key_to_glfw(Keys key) {
        switch (key) {
            case Keys::KeySpace:
                return GLFW_KEY_SPACE;
            case Keys::KeyApostrophe:
                return GLFW_KEY_APOSTROPHE;
            case Keys::KeyComma:
                return GLFW_KEY_COMMA;
            case Keys::KeyMinus:
                return GLFW_KEY_MINUS;
            case Keys::KeyPeriod:
                return GLFW_KEY_PERIOD;
            case Keys::KeySlash:
                return GLFW_KEY_SLASH;
            case Keys::Key0:
                return GLFW_KEY_0;
            case Keys::Key1:
                return GLFW_KEY_1;
            case Keys::Key2:
                return GLFW_KEY_2;
            case Keys::Key3:
                return GLFW_KEY_3;
            case Keys::Key4:
                return GLFW_KEY_4;
            case Keys::Key5:
                return GLFW_KEY_5;
            case Keys::Key6:
                return GLFW_KEY_6;
            case Keys::Key7:
                return GLFW_KEY_7;
            case Keys::Key8:
                return GLFW_KEY_8;
            case Keys::Key9:
                return GLFW_KEY_9;
            case Keys::KeySemicolon:
                return GLFW_KEY_SEMICOLON;
            case Keys::KeyEqual:
                return GLFW_KEY_EQUAL;
            case Keys::KeyA:
                return GLFW_KEY_A;
            case Keys::KeyB:
                return GLFW_KEY_B;
            case Keys::KeyC:
                return GLFW_KEY_C;
            case Keys::KeyD:
                return GLFW_KEY_D;
            case Keys::KeyE:
                return GLFW_KEY_E;
            case Keys::KeyF:
                return GLFW_KEY_F;
            case Keys::KeyG:
                return GLFW_KEY_G;
            case Keys::KeyH:
                return GLFW_KEY_H;
            case Keys::KeyI:
                return GLFW_KEY_I;
            case Keys::KeyJ:
                return GLFW_KEY_J;
            case Keys::KeyK:
                return GLFW_KEY_K;
            case Keys::KeyL:
                return GLFW_KEY_L;
            case Keys::KeyM:
                return GLFW_KEY_M;
            case Keys::KeyN:
                return GLFW_KEY_N;
            case Keys::KeyO:
                return GLFW_KEY_O;
            case Keys::KeyP:
                return GLFW_KEY_P;
            case Keys::KeyQ:
                return GLFW_KEY_Q;
            case Keys::KeyR:
                return GLFW_KEY_R;
            case Keys::KeyS:
                return GLFW_KEY_S;
            case Keys::KeyT:
                return GLFW_KEY_T;
            case Keys::KeyU:
                return GLFW_KEY_U;
            case Keys::KeyV:
                return GLFW_KEY_V;
            case Keys::KeyW:
                return GLFW_KEY_W;
            case Keys::KeyX:
                return GLFW_KEY_X;
            case Keys::KeyY:
                return GLFW_KEY_Y;
            case Keys::KeyZ:
                return GLFW_KEY_Z;
            case Keys::KeyLeftBracket:
                return GLFW_KEY_LEFT_BRACKET;
            case Keys::KeyBackslash:
                return GLFW_KEY_BACKSLASH;
            case Keys::KeyRightBracket:
                return GLFW_KEY_RIGHT_BRACKET;
            case Keys::KeyGraveAccent:
                return GLFW_KEY_GRAVE_ACCENT;
            case Keys::KeyWorld1:
                return GLFW_KEY_WORLD_1;
            case Keys::KeyWorld2:
                return GLFW_KEY_WORLD_2;
            case Keys::KeyEscape:
                return GLFW_KEY_ESCAPE;
            case Keys::KeyEnter:
                return GLFW_KEY_ENTER;
            case Keys::KeyTab:
                return GLFW_KEY_TAB;
            case Keys::KeyBackspace:
                return GLFW_KEY_BACKSPACE;
            case Keys::KeyInsert:
                return GLFW_KEY_INSERT;
            case Keys::KeyDelete:
                return GLFW_KEY_DELETE;
            case Keys::KeyRight:
                return GLFW_KEY_RIGHT;
            case Keys::KeyLeft:
                return GLFW_KEY_LEFT;
            case Keys::KeyDown:
                return GLFW_KEY_DOWN;
            case Keys::KeyUp:
                return GLFW_KEY_UP;
            case Keys::KeyPageUp:
                return GLFW_KEY_PAGE_UP;
            case Keys::KeyPageDown:
                return GLFW_KEY_PAGE_DOWN;
            case Keys::KeyHome:
                return GLFW_KEY_HOME;
            case Keys::KeyEnd:
                return GLFW_KEY_END;
            case Keys::KeyCapsLock:
                return GLFW_KEY_CAPS_LOCK;
            case Keys::KeyScrollLock:
                return GLFW_KEY_SCROLL_LOCK;
            case Keys::KeyNumLock:
                return GLFW_KEY_NUM_LOCK;
            case Keys::KeyPrintScreen:
                return GLFW_KEY_PRINT_SCREEN;
            case Keys::KeyPause:
                return GLFW_KEY_PAUSE;
            case Keys::KeyF1:
                return GLFW_KEY_F1;
            case Keys::KeyF2:
                return GLFW_KEY_F2;
            case Keys::KeyF3:
                return GLFW_KEY_F3;
            case Keys::KeyF4:
                return GLFW_KEY_F4;
            case Keys::KeyF5:
                return GLFW_KEY_F5;
            case Keys::KeyF6:
                return GLFW_KEY_F6;
            case Keys::KeyF7:
                return GLFW_KEY_F7;
            case Keys::KeyF8:
                return GLFW_KEY_F8;
            case Keys::KeyF9:
                return GLFW_KEY_F9;
            case Keys::KeyF10:
                return GLFW_KEY_F10;
            case Keys::KeyF11:
                return GLFW_KEY_F11;
            case Keys::KeyF12:
                return GLFW_KEY_F12;
            case Keys::KeyF13:
                return GLFW_KEY_F13;
            case Keys::KeyF14:
                return GLFW_KEY_F14;
            case Keys::KeyF15:
                return GLFW_KEY_F15;
            case Keys::KeyF16:
                return GLFW_KEY_F16;
            case Keys::KeyF17:
                return GLFW_KEY_F17;
            case Keys::KeyF18:
                return GLFW_KEY_F18;
            case Keys::KeyF19:
                return GLFW_KEY_F19;
            case Keys::KeyF20:
                return GLFW_KEY_F20;
            case Keys::KeyF21:
                return GLFW_KEY_F21;
            case Keys::KeyF22:
                return GLFW_KEY_F22;
            case Keys::KeyF23:
                return GLFW_KEY_F23;
            case Keys::KeyF24:
                return GLFW_KEY_F24;
            case Keys::KeyF25:
                return GLFW_KEY_F25;
            case Keys::KeyKp0:
                return GLFW_KEY_KP_0;
            case Keys::KeyKp1:
                return GLFW_KEY_KP_1;
            case Keys::KeyKp2:
                return GLFW_KEY_KP_2;
            case Keys::KeyKp3:
                return GLFW_KEY_KP_3;
            case Keys::KeyKp4:
                return GLFW_KEY_KP_4;
            case Keys::KeyKp5:
                return GLFW_KEY_KP_5;
            case Keys::KeyKp6:
                return GLFW_KEY_KP_6;
            case Keys::KeyKp7:
                return GLFW_KEY_KP_7;
            case Keys::KeyKp8:
                return GLFW_KEY_KP_8;
            case Keys::KeyKp9:
                return GLFW_KEY_KP_9;
            case Keys::KeyKpDecimal:
                return GLFW_KEY_KP_DECIMAL;
            case Keys::KeyKpDivide:
                return GLFW_KEY_KP_DIVIDE;
            case Keys::KeyKpMultiply:
                return GLFW_KEY_KP_MULTIPLY;
            case Keys::KeyKpSubtract:
                return GLFW_KEY_KP_SUBTRACT;
            case Keys::KeyKpAdd:
                return GLFW_KEY_KP_ADD;
            case Keys::KeyKpEnter:
                return GLFW_KEY_KP_ENTER;
            case Keys::KeyKpEqual:
                return GLFW_KEY_KP_EQUAL;
            case Keys::KeyLeftShift:
                return GLFW_KEY_LEFT_SHIFT;
            case Keys::KeyLeftControl:
                return GLFW_KEY_LEFT_CONTROL;
            case Keys::KeyLeftAlt:
                return GLFW_KEY_LEFT_ALT;
            case Keys::KeyLeftSuper:
                return GLFW_KEY_LEFT_SUPER;
            case Keys::KeyRightShift:
                return GLFW_KEY_RIGHT_SHIFT;
            case Keys::KeyRightControl:
                return GLFW_KEY_RIGHT_CONTROL;
            case Keys::KeyRightAlt:
                return GLFW_KEY_RIGHT_ALT;
            case Keys::KeyRightSuper:
                return GLFW_KEY_RIGHT_SUPER;
            case Keys::KeyMenu:
                return GLFW_KEY_MENU;
            default:
                assert(false);
                throw std::runtime_error("invalid key enum");
        }
    }
} // namespace sly::gl
