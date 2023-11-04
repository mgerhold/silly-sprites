#pragma once

#include <cassert>
#include <exception>
#include <string>

namespace sly::gl {

    enum class GlErrorType {
        FailedToInitializeGlfw,
        UnableToCreateGlfwContext,
        FailedToCreateWindow,
        FailedToInitializeGlad,
        FailedToCompileShader,
        FailedToLinkShaderProgram,
        InvalidShaderType,
        FailedToCreateShaderProgram,
        FailedToCreateShader,
        EmptyShaderSource,
        NoShaderSource,
    };

    class GlError : public std::exception {
    private:
        GlErrorType m_type;
        std::string m_message;

    public:
        explicit GlError(GlErrorType type);
        GlError(GlErrorType type, std::string_view message);

        [[nodiscard]] char const* what() const noexcept override;
    };

    void error_callback(int code, char const* message);

} // namespace sly::gl
