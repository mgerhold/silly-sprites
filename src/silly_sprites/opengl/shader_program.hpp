#pragma once

#include "../types.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>
#include <string_view>
#include <tl/optional.hpp>

namespace sly::gl {
    class ShaderProgram final {
    public:
        enum class Type : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };

    private:
        GLuint m_program_name;

        [[nodiscard]] static constexpr std::string_view get_name_from_type(Type type);
        [[nodiscard]] GLint compile(Type type, std::string_view source);
        void attach_shader(GLint shader) const;
        void link_program() const;

    public:
        ShaderProgram(
                std::string_view vertex_source,
                std::string_view geometry_source,
                std::string_view fragment_source
        );
        ShaderProgram(std::string_view vertex_source, std::string_view fragment_source);
        ShaderProgram(ShaderProgram const&) = delete;
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram const&) = delete;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;
        ~ShaderProgram();

        void use();
    };
} // namespace sly::gl
