#pragma once
#include "window.hpp"
#include "key.hpp"
#include "mouse.hpp"
#include <array>
#include <magic_enum.hpp>

namespace sly::gl {
	class Input final {
	private:
		static inline std::array<bool, magic_enum::enum_count<Key>()> current_keys{  };
		static inline std::array<bool, magic_enum::enum_count<Key>()> last_keys{  };

		static inline std::array<bool, magic_enum::enum_count<Mouse>()> current_mouse{  };
		static inline std::array<bool, magic_enum::enum_count<Mouse>()> last_mouse{  };

		using mouse_pos_ty = std::pair<double, double>;
		static inline mouse_pos_ty mouse_position{ }; 

		static void update_keys(Window const& window);
		static void update_mouse(Window const& window);
		static void update_mouse_position(Window const& window);

	public:
		static void update(Window const& window);

		[[nodiscard]] static mouse_pos_ty get_mouse_position();

		// single frame
		[[nodiscard]] static bool is_key_down(Key key);
		[[nodiscard]] static bool is_key_up(Key key);

		// multi-frame
		[[nodiscard]] static bool is_key_pressed(Key key);
		[[nodiscard]] static bool is_key_released(Key key);

		[[nodiscard]] static bool is_key_hold(Key key);
		[[nodiscard]] static bool is_key_raised(Key key);

		// single frame
		[[nodiscard]] static bool is_mouse_down(Mouse key);
		[[nodiscard]] static bool is_mouse_up(Mouse key);

		// multi-frame
		[[nodiscard]] static bool is_mouse_pressed(Mouse key);
		[[nodiscard]] static bool is_mouse_released(Mouse key);

		[[nodiscard]] static bool is_mouse_hold(Mouse key);
		[[nodiscard]] static bool is_mouse_raised(Mouse key);
	};
}
