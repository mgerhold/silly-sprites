#pragma once

#define GLFW_INCLUDE_NONE
#include "gl_error.hpp"
#include "glfw_context.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <tl/expected.hpp>

namespace sly::gl {

	class Window final {
		private:
            GlfwContext m_context;

            using Deleter = void(*)(GLFWwindow*);
            std::unique_ptr<GLFWwindow, Deleter> m_window;

			Window(GlfwContext context, GLFWwindow* window);
			[[nodiscard]] GLFWwindow* get() const;

		public:
			[[nodiscard]] static tl::expected<Window, GlError> create(int width, int height);

			[[nodiscard]] bool should_close() const;
			void swap_buffers();
	};
}