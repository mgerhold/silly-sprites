#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <tl/expected.hpp>
#include "gl_error.hpp"

namespace sly::gl {
	
	class Window final {
		private:
			GLFWwindow* m_window;
			Window(GLFWwindow* window); // to force to use create()

			[[nodiscard]] GLFWwindow* get() const;

		public:
			Window(Window const&) = delete;
			Window(Window&&) = delete;
			Window& operator=(Window const&) = delete;
			Window& operator=(Window&&) = delete;
			~Window();

			[[nodiscard]] static tl::expected<Window,WindowError> create(int width, int height);

			[[nodiscard]] bool should_close() const;
			void swap_buffers();

	};
}
