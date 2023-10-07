#pragma once
#include "shader_type.hpp"
#include <glad/gl.h>

namespace sly::gl {
    class Shader final {
    public:
    private:
        GLuint m_name = 0;
        bool m_valid = false;

    public:
        Shader(ShaderType type, std::string_view const source);
        Shader(Shader const&) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader const&) = delete;
        Shader& operator=(Shader&& other) noexcept;
        ~Shader();

        [[nodiscard]] bool is_valid() const;
        [[nodiscard]] GLuint get_name() const;

    private:
    };
} // namespace sly::gl
