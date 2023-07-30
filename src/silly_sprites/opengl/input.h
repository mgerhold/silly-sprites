#pragma once
#include "window.hpp"
#include "keys.hpp"
#include <array>
#include <magic_enum.hpp>

namespace sly::gl {
	class Input final {
	private:
		enum class KeyState {
			Pressed,
			Down,
			Release,
			Up,
		};

		static inline std::array<bool, magic_enum::enum_count<Keys>()> current_keys{  };
		static inline std::array<bool, magic_enum::enum_count<Keys>()> last_keys{  };
	public:
		
		static void update_keys(Window const& window);

		// single frame
		[[nodiscard]] static bool is_key_down(Keys key);
		[[nodiscard]] static bool is_key_up(Keys key);

		// multi-frame
		[[nodiscard]] static bool is_key_pressed(Keys key);
		[[nodiscard]] static bool is_key_released(Keys key);

		[[nodiscard]] static bool is_key_hold(Keys key);
		[[nodiscard]] static bool is_key_raised(Keys key);
	};
}
