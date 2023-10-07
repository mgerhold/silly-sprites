#include "error.hpp"

namespace sly::gl {
    GlError::GlError(GlErrorType const type) : GlError{ type, "" } { }

    GlError::GlError(GlErrorType const type, std::string message) : m_type{ type }, m_message{ std::move(message) } {
        auto const type_name = magic_enum::enum_name(m_type);
        if (m_message.empty()) {
            m_message = type_name;
        } else {
            m_message = fmt::format("{};\n{}", type_name, m_message);
        }
    }

    [[nodiscard]] char const* GlError::what() const noexcept {
        return m_message.c_str();
    }
} // namespace sly::gl
