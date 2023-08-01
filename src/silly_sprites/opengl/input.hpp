#pragma once
#include "../types.hpp"
#include "key.hpp"
#include "mouse.hpp"
#include "window.hpp"
#include <array>
#include <glm/glm.hpp>
#include <magic_enum.hpp>

namespace sly::gl {
    class Input final {
    private:
        static constexpr auto num_key = magic_enum::enum_count<Key>();
        static constexpr auto num_mouse = magic_enum::enum_count<MouseButton>();

        static inline std::array<bool, num_key> s_current_keys{};
        static inline std::array<bool, num_key> s_last_keys{};

        static inline std::array<bool, num_mouse> s_current_mouse{};
        static inline std::array<bool, num_mouse> s_last_mouse{};

        static inline Vec2 s_mouse_position{};

        static void update_keys(Window const& window);
        static void update_mouse(Window const& window);
        static void update_mouse_position(Window const& window);

    public:
        static void update(Window const& window);

        [[nodiscard]] static Vec2 get_mouse_position();

        [[nodiscard]] static bool is_key_down(Key key);
        [[nodiscard]] static bool is_key_up(Key key);
        [[nodiscard]] static bool is_key_pressed(Key key);
        [[nodiscard]] static bool is_key_released(Key key);

        [[nodiscard]] static bool is_mouse_down(MouseButton key);
        [[nodiscard]] static bool is_mouse_up(MouseButton key);
        [[nodiscard]] static bool is_mouse_pressed(MouseButton key);
        [[nodiscard]] static bool is_mouse_released(MouseButton key);
    };
} // namespace sly::gl
