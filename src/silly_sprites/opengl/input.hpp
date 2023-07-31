#pragma once
#include "window.hpp"
#include "key.hpp"
#include "mouse.hpp"
#include <array>
#include <magic_enum.hpp>
#include <glm/glm.hpp>

namespace sly::gl {
	class Input final {
	private:
		static constexpr auto num_key = magic_enum::enum_count<Key>(); 
		static constexpr auto num_mouse = magic_enum::enum_count<Mouse>();

		static inline std::array<bool, num_key> current_keys{  };
		static inline std::array<bool, num_key> last_keys{  };

		static inline std::array<bool, num_mouse> current_mouse{  };
		static inline std::array<bool, num_mouse> last_mouse{  };

		using Vec2 = glm::vec2;
		static inline Vec2 mouse_position{ }; 

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

		[[nodiscard]] static bool is_mouse_down(Mouse key);
		[[nodiscard]] static bool is_mouse_up(Mouse key);
		[[nodiscard]] static bool is_mouse_pressed(Mouse key);
		[[nodiscard]] static bool is_mouse_released(Mouse key);
	};
}
