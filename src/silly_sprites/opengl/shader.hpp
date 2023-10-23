#pragma once
#include "shader_type.hpp"
#include "error.hpp"
#include <glad/gl.h>
#include <tl/expected.hpp>

namespace sly::gl {
    class Shader final {
    private:
        GLuint m_name = 0;
        Shader(GLuint name);

    public:
        Shader(Shader const&) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader const&) = delete;
        Shader& operator=(Shader&& other) noexcept;
        ~Shader();

        [[nodiscard]] static tl::expected<Shader, GlError> create(ShaderType type, std::string_view const source);

        [[nodiscard]] GLuint name() const;
    };
} // namespace sly::gl
