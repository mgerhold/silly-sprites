#pragma once

#include "spdlog/spdlog.h"
#include "../include/magic_enum_wrapper.hpp"
#include <string>
#include <cassert>
#include <exception>

namespace sly::gl {

    enum class GLErrorType {
        FailedToInitializeGlfw,
        UnableToCreateGlfwContext,
        FailedToCreateWindow,
        FailedToInitializeGlad,
        FailedToCompileVertexShader,
        FailedToCompileGeometryShader,
        FailedToCompileFragmentShader,
        FailedToLinkShaderProgram,
    };

    class GLError : public std::exception {
    private:
        GLErrorType m_type;
        std::string m_message;

    public:
        explicit GLError(GLErrorType type);
        GLError(GLErrorType type, std::string message);

        [[nodiscard]] char const* what() const noexcept override;
    };

    inline void error_callback(int code, char const* message) {
        spdlog::critical("GLFW error ({}): {}", code, message);
    }

} // namespace sly::gl
