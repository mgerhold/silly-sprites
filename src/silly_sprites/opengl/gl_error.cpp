#include "gl_error.hpp"

namespace sly::gl {

    WindowError::WindowError(std::string_view message) 
        : m_message{ message } { }
    std::string_view sly::gl::WindowError::get_message() const {
        return m_message;
    }

} // namespace sly::gl