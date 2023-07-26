#pragma once

#include <string>

namespace sly::gl {
	
	class WindowError final {
    private:
		std::string m_message;

    public:
		WindowError(std::string_view message);
		[[nodiscard]] std::string_view get_message() const;
	};	
}