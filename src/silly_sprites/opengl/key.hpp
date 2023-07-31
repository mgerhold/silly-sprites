#pragma once
namespace sly::gl {
    enum class Key {
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
    [[nodiscard]] constexpr Key glfw_to_key(int glfw) {
        switch (glfw) {
            case GLFW_KEY_SPACE:
                return Key::KeySpace;
            case GLFW_KEY_APOSTROPHE:
                return Key::KeyApostrophe;
            case GLFW_KEY_COMMA:
                return Key::KeyComma;
            case GLFW_KEY_MINUS:
                return Key::KeyMinus;
            case GLFW_KEY_PERIOD:
                return Key::KeyPeriod;
            case GLFW_KEY_SLASH:
                return Key::KeySlash;
            case GLFW_KEY_0:
                return Key::Key0;
            case GLFW_KEY_1:
                return Key::Key1;
            case GLFW_KEY_2:
                return Key::Key2;
            case GLFW_KEY_3:
                return Key::Key3;
            case GLFW_KEY_4:
                return Key::Key4;
            case GLFW_KEY_5:
                return Key::Key5;
            case GLFW_KEY_6:
                return Key::Key6;
            case GLFW_KEY_7:
                return Key::Key7;
            case GLFW_KEY_8:
                return Key::Key8;
            case GLFW_KEY_9:
                return Key::Key9;
            case GLFW_KEY_SEMICOLON:
                return Key::KeySemicolon;
            case GLFW_KEY_EQUAL:
                return Key::KeyEqual;
            case GLFW_KEY_A:
                return Key::KeyA;
            case GLFW_KEY_B:
                return Key::KeyB;
            case GLFW_KEY_C:
                return Key::KeyC;
            case GLFW_KEY_D:
                return Key::KeyD;
            case GLFW_KEY_E:
                return Key::KeyE;
            case GLFW_KEY_F:
                return Key::KeyF;
            case GLFW_KEY_G:
                return Key::KeyG;
            case GLFW_KEY_H:
                return Key::KeyH;
            case GLFW_KEY_I:
                return Key::KeyI;
            case GLFW_KEY_J:
                return Key::KeyJ;
            case GLFW_KEY_K:
                return Key::KeyK;
            case GLFW_KEY_L:
                return Key::KeyL;
            case GLFW_KEY_M:
                return Key::KeyM;
            case GLFW_KEY_N:
                return Key::KeyN;
            case GLFW_KEY_O:
                return Key::KeyO;
            case GLFW_KEY_P:
                return Key::KeyP;
            case GLFW_KEY_Q:
                return Key::KeyQ;
            case GLFW_KEY_R:
                return Key::KeyR;
            case GLFW_KEY_S:
                return Key::KeyS;
            case GLFW_KEY_T:
                return Key::KeyT;
            case GLFW_KEY_U:
                return Key::KeyU;
            case GLFW_KEY_V:
                return Key::KeyV;
            case GLFW_KEY_W:
                return Key::KeyW;
            case GLFW_KEY_X:
                return Key::KeyX;
            case GLFW_KEY_Y:
                return Key::KeyY;
            case GLFW_KEY_Z:
                return Key::KeyZ;
            case GLFW_KEY_LEFT_BRACKET:
                return Key::KeyLeftBracket;
            case GLFW_KEY_BACKSLASH:
                return Key::KeyBackslash;
            case GLFW_KEY_RIGHT_BRACKET:
                return Key::KeyRightBracket;
            case GLFW_KEY_GRAVE_ACCENT:
                return Key::KeyGraveAccent;
            case GLFW_KEY_WORLD_1:
                return Key::KeyWorld1;
            case GLFW_KEY_WORLD_2:
                return Key::KeyWorld2;
            case GLFW_KEY_ESCAPE:
                return Key::KeyEscape;
            case GLFW_KEY_ENTER:
                return Key::KeyEnter;
            case GLFW_KEY_TAB:
                return Key::KeyTab;
            case GLFW_KEY_BACKSPACE:
                return Key::KeyBackspace;
            case GLFW_KEY_INSERT:
                return Key::KeyInsert;
            case GLFW_KEY_DELETE:
                return Key::KeyDelete;
            case GLFW_KEY_RIGHT:
                return Key::KeyRight;
            case GLFW_KEY_LEFT:
                return Key::KeyLeft;
            case GLFW_KEY_DOWN:
                return Key::KeyDown;
            case GLFW_KEY_UP:
                return Key::KeyUp;
            case GLFW_KEY_PAGE_UP:
                return Key::KeyPageUp;
            case GLFW_KEY_PAGE_DOWN:
                return Key::KeyPageDown;
            case GLFW_KEY_HOME:
                return Key::KeyHome;
            case GLFW_KEY_END:
                return Key::KeyEnd;
            case GLFW_KEY_CAPS_LOCK:
                return Key::KeyCapsLock;
            case GLFW_KEY_SCROLL_LOCK:
                return Key::KeyScrollLock;
            case GLFW_KEY_NUM_LOCK:
                return Key::KeyNumLock;
            case GLFW_KEY_PRINT_SCREEN:
                return Key::KeyPrintScreen;
            case GLFW_KEY_PAUSE:
                return Key::KeyPause;
            case GLFW_KEY_F1:
                return Key::KeyF1;
            case GLFW_KEY_F2:
                return Key::KeyF2;
            case GLFW_KEY_F3:
                return Key::KeyF3;
            case GLFW_KEY_F4:
                return Key::KeyF4;
            case GLFW_KEY_F5:
                return Key::KeyF5;
            case GLFW_KEY_F6:
                return Key::KeyF6;
            case GLFW_KEY_F7:
                return Key::KeyF7;
            case GLFW_KEY_F8:
                return Key::KeyF8;
            case GLFW_KEY_F9:
                return Key::KeyF9;
            case GLFW_KEY_F10:
                return Key::KeyF10;
            case GLFW_KEY_F11:
                return Key::KeyF11;
            case GLFW_KEY_F12:
                return Key::KeyF12;
            case GLFW_KEY_F13:
                return Key::KeyF13;
            case GLFW_KEY_F14:
                return Key::KeyF14;
            case GLFW_KEY_F15:
                return Key::KeyF15;
            case GLFW_KEY_F16:
                return Key::KeyF16;
            case GLFW_KEY_F17:
                return Key::KeyF17;
            case GLFW_KEY_F18:
                return Key::KeyF18;
            case GLFW_KEY_F19:
                return Key::KeyF19;
            case GLFW_KEY_F20:
                return Key::KeyF20;
            case GLFW_KEY_F21:
                return Key::KeyF21;
            case GLFW_KEY_F22:
                return Key::KeyF22;
            case GLFW_KEY_F23:
                return Key::KeyF23;
            case GLFW_KEY_F24:
                return Key::KeyF24;
            case GLFW_KEY_F25:
                return Key::KeyF25;
            case GLFW_KEY_KP_0:
                return Key::KeyKp0;
            case GLFW_KEY_KP_1:
                return Key::KeyKp1;
            case GLFW_KEY_KP_2:
                return Key::KeyKp2;
            case GLFW_KEY_KP_3:
                return Key::KeyKp3;
            case GLFW_KEY_KP_4:
                return Key::KeyKp4;
            case GLFW_KEY_KP_5:
                return Key::KeyKp5;
            case GLFW_KEY_KP_6:
                return Key::KeyKp6;
            case GLFW_KEY_KP_7:
                return Key::KeyKp7;
            case GLFW_KEY_KP_8:
                return Key::KeyKp8;
            case GLFW_KEY_KP_9:
                return Key::KeyKp9;
            case GLFW_KEY_KP_DECIMAL:
                return Key::KeyKpDecimal;
            case GLFW_KEY_KP_DIVIDE:
                return Key::KeyKpDivide;
            case GLFW_KEY_KP_MULTIPLY:
                return Key::KeyKpMultiply;
            case GLFW_KEY_KP_SUBTRACT:
                return Key::KeyKpSubtract;
            case GLFW_KEY_KP_ADD:
                return Key::KeyKpAdd;
            case GLFW_KEY_KP_ENTER:
                return Key::KeyKpEnter;
            case GLFW_KEY_KP_EQUAL:
                return Key::KeyKpEqual;
            case GLFW_KEY_LEFT_SHIFT:
                return Key::KeyLeftShift;
            case GLFW_KEY_LEFT_CONTROL:
                return Key::KeyLeftControl;
            case GLFW_KEY_LEFT_ALT:
                return Key::KeyLeftAlt;
            case GLFW_KEY_LEFT_SUPER:
                return Key::KeyLeftSuper;
            case GLFW_KEY_RIGHT_SHIFT:
                return Key::KeyRightShift;
            case GLFW_KEY_RIGHT_CONTROL:
                return Key::KeyRightControl;
            case GLFW_KEY_RIGHT_ALT:
                return Key::KeyRightAlt;
            case GLFW_KEY_RIGHT_SUPER:
                return Key::KeyRightSuper;
            case GLFW_KEY_MENU:
                return Key::KeyMenu;
            default:
                assert(false);
                throw std::runtime_error("invalid glfw key define");
        }
    }
    [[nodiscard]] constexpr int key_to_glfw(Key key) {
        switch (key) {
            case Key::KeySpace:
                return GLFW_KEY_SPACE;
            case Key::KeyApostrophe:
                return GLFW_KEY_APOSTROPHE;
            case Key::KeyComma:
                return GLFW_KEY_COMMA;
            case Key::KeyMinus:
                return GLFW_KEY_MINUS;
            case Key::KeyPeriod:
                return GLFW_KEY_PERIOD;
            case Key::KeySlash:
                return GLFW_KEY_SLASH;
            case Key::Key0:
                return GLFW_KEY_0;
            case Key::Key1:
                return GLFW_KEY_1;
            case Key::Key2:
                return GLFW_KEY_2;
            case Key::Key3:
                return GLFW_KEY_3;
            case Key::Key4:
                return GLFW_KEY_4;
            case Key::Key5:
                return GLFW_KEY_5;
            case Key::Key6:
                return GLFW_KEY_6;
            case Key::Key7:
                return GLFW_KEY_7;
            case Key::Key8:
                return GLFW_KEY_8;
            case Key::Key9:
                return GLFW_KEY_9;
            case Key::KeySemicolon:
                return GLFW_KEY_SEMICOLON;
            case Key::KeyEqual:
                return GLFW_KEY_EQUAL;
            case Key::KeyA:
                return GLFW_KEY_A;
            case Key::KeyB:
                return GLFW_KEY_B;
            case Key::KeyC:
                return GLFW_KEY_C;
            case Key::KeyD:
                return GLFW_KEY_D;
            case Key::KeyE:
                return GLFW_KEY_E;
            case Key::KeyF:
                return GLFW_KEY_F;
            case Key::KeyG:
                return GLFW_KEY_G;
            case Key::KeyH:
                return GLFW_KEY_H;
            case Key::KeyI:
                return GLFW_KEY_I;
            case Key::KeyJ:
                return GLFW_KEY_J;
            case Key::KeyK:
                return GLFW_KEY_K;
            case Key::KeyL:
                return GLFW_KEY_L;
            case Key::KeyM:
                return GLFW_KEY_M;
            case Key::KeyN:
                return GLFW_KEY_N;
            case Key::KeyO:
                return GLFW_KEY_O;
            case Key::KeyP:
                return GLFW_KEY_P;
            case Key::KeyQ:
                return GLFW_KEY_Q;
            case Key::KeyR:
                return GLFW_KEY_R;
            case Key::KeyS:
                return GLFW_KEY_S;
            case Key::KeyT:
                return GLFW_KEY_T;
            case Key::KeyU:
                return GLFW_KEY_U;
            case Key::KeyV:
                return GLFW_KEY_V;
            case Key::KeyW:
                return GLFW_KEY_W;
            case Key::KeyX:
                return GLFW_KEY_X;
            case Key::KeyY:
                return GLFW_KEY_Y;
            case Key::KeyZ:
                return GLFW_KEY_Z;
            case Key::KeyLeftBracket:
                return GLFW_KEY_LEFT_BRACKET;
            case Key::KeyBackslash:
                return GLFW_KEY_BACKSLASH;
            case Key::KeyRightBracket:
                return GLFW_KEY_RIGHT_BRACKET;
            case Key::KeyGraveAccent:
                return GLFW_KEY_GRAVE_ACCENT;
            case Key::KeyWorld1:
                return GLFW_KEY_WORLD_1;
            case Key::KeyWorld2:
                return GLFW_KEY_WORLD_2;
            case Key::KeyEscape:
                return GLFW_KEY_ESCAPE;
            case Key::KeyEnter:
                return GLFW_KEY_ENTER;
            case Key::KeyTab:
                return GLFW_KEY_TAB;
            case Key::KeyBackspace:
                return GLFW_KEY_BACKSPACE;
            case Key::KeyInsert:
                return GLFW_KEY_INSERT;
            case Key::KeyDelete:
                return GLFW_KEY_DELETE;
            case Key::KeyRight:
                return GLFW_KEY_RIGHT;
            case Key::KeyLeft:
                return GLFW_KEY_LEFT;
            case Key::KeyDown:
                return GLFW_KEY_DOWN;
            case Key::KeyUp:
                return GLFW_KEY_UP;
            case Key::KeyPageUp:
                return GLFW_KEY_PAGE_UP;
            case Key::KeyPageDown:
                return GLFW_KEY_PAGE_DOWN;
            case Key::KeyHome:
                return GLFW_KEY_HOME;
            case Key::KeyEnd:
                return GLFW_KEY_END;
            case Key::KeyCapsLock:
                return GLFW_KEY_CAPS_LOCK;
            case Key::KeyScrollLock:
                return GLFW_KEY_SCROLL_LOCK;
            case Key::KeyNumLock:
                return GLFW_KEY_NUM_LOCK;
            case Key::KeyPrintScreen:
                return GLFW_KEY_PRINT_SCREEN;
            case Key::KeyPause:
                return GLFW_KEY_PAUSE;
            case Key::KeyF1:
                return GLFW_KEY_F1;
            case Key::KeyF2:
                return GLFW_KEY_F2;
            case Key::KeyF3:
                return GLFW_KEY_F3;
            case Key::KeyF4:
                return GLFW_KEY_F4;
            case Key::KeyF5:
                return GLFW_KEY_F5;
            case Key::KeyF6:
                return GLFW_KEY_F6;
            case Key::KeyF7:
                return GLFW_KEY_F7;
            case Key::KeyF8:
                return GLFW_KEY_F8;
            case Key::KeyF9:
                return GLFW_KEY_F9;
            case Key::KeyF10:
                return GLFW_KEY_F10;
            case Key::KeyF11:
                return GLFW_KEY_F11;
            case Key::KeyF12:
                return GLFW_KEY_F12;
            case Key::KeyF13:
                return GLFW_KEY_F13;
            case Key::KeyF14:
                return GLFW_KEY_F14;
            case Key::KeyF15:
                return GLFW_KEY_F15;
            case Key::KeyF16:
                return GLFW_KEY_F16;
            case Key::KeyF17:
                return GLFW_KEY_F17;
            case Key::KeyF18:
                return GLFW_KEY_F18;
            case Key::KeyF19:
                return GLFW_KEY_F19;
            case Key::KeyF20:
                return GLFW_KEY_F20;
            case Key::KeyF21:
                return GLFW_KEY_F21;
            case Key::KeyF22:
                return GLFW_KEY_F22;
            case Key::KeyF23:
                return GLFW_KEY_F23;
            case Key::KeyF24:
                return GLFW_KEY_F24;
            case Key::KeyF25:
                return GLFW_KEY_F25;
            case Key::KeyKp0:
                return GLFW_KEY_KP_0;
            case Key::KeyKp1:
                return GLFW_KEY_KP_1;
            case Key::KeyKp2:
                return GLFW_KEY_KP_2;
            case Key::KeyKp3:
                return GLFW_KEY_KP_3;
            case Key::KeyKp4:
                return GLFW_KEY_KP_4;
            case Key::KeyKp5:
                return GLFW_KEY_KP_5;
            case Key::KeyKp6:
                return GLFW_KEY_KP_6;
            case Key::KeyKp7:
                return GLFW_KEY_KP_7;
            case Key::KeyKp8:
                return GLFW_KEY_KP_8;
            case Key::KeyKp9:
                return GLFW_KEY_KP_9;
            case Key::KeyKpDecimal:
                return GLFW_KEY_KP_DECIMAL;
            case Key::KeyKpDivide:
                return GLFW_KEY_KP_DIVIDE;
            case Key::KeyKpMultiply:
                return GLFW_KEY_KP_MULTIPLY;
            case Key::KeyKpSubtract:
                return GLFW_KEY_KP_SUBTRACT;
            case Key::KeyKpAdd:
                return GLFW_KEY_KP_ADD;
            case Key::KeyKpEnter:
                return GLFW_KEY_KP_ENTER;
            case Key::KeyKpEqual:
                return GLFW_KEY_KP_EQUAL;
            case Key::KeyLeftShift:
                return GLFW_KEY_LEFT_SHIFT;
            case Key::KeyLeftControl:
                return GLFW_KEY_LEFT_CONTROL;
            case Key::KeyLeftAlt:
                return GLFW_KEY_LEFT_ALT;
            case Key::KeyLeftSuper:
                return GLFW_KEY_LEFT_SUPER;
            case Key::KeyRightShift:
                return GLFW_KEY_RIGHT_SHIFT;
            case Key::KeyRightControl:
                return GLFW_KEY_RIGHT_CONTROL;
            case Key::KeyRightAlt:
                return GLFW_KEY_RIGHT_ALT;
            case Key::KeyRightSuper:
                return GLFW_KEY_RIGHT_SUPER;
            case Key::KeyMenu:
                return GLFW_KEY_MENU;
            default:
                assert(false);
                throw std::runtime_error("invalid key enum");
        }
    }
} // namespace sly::gl
