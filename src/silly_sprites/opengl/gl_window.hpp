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

    public:
		Window(GLFWwindow* window);
		~Window();


		[[nodiscard]] static tl::expected<Window,WindowError> create(int width, int height);
		[[nodiscard]] GLFWwindow* get() const;
	};
}