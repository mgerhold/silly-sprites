#pragma once

#include <string>

namespace sly::gl {

    class WindowError final {
        private:
            std::string m_message;

        public:
            WindowError(std::string message);
            [[nodiscard]] std::string_view get_message() const;
    };
} // namespace sly::gl
