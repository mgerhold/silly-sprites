#include "error.hpp"

#include "../include/magic_enum_wrapper.hpp"
#include <spdlog/spdlog.h>

namespace sly::gl {
    GlError::GlError(GlErrorType const type) : GlError{ type, "" } { }

    GlError::GlError(GlErrorType const type, std::string_view const message) : m_type{ type } {
        auto const type_name = magic_enum::enum_name(m_type);
        if (message.empty()) {
            m_message = type_name;
        } else {
            m_message = fmt::format("{};\n{}", type_name, message);
        }
    }

    [[nodiscard]] char const* GlError::what() const noexcept {
        return m_message.c_str();
    }

    void error_callback(int code, char const* message) {
        spdlog::critical("GLFW error ({}): {}", code, message);
    }
} // namespace sly::gl
