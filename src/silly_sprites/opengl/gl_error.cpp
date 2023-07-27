#include "gl_error.hpp"

namespace sly::gl {

    WindowError::WindowError(std::string message)
        : m_message{ std::move(message) } { }

    [[nodiscard]] std::string_view sly::gl::WindowError::get_message() const {
        return m_message;
    }

} // namespace sly::gl
