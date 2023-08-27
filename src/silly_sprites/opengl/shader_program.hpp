#pragma once

#include "../types.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>
#include <string_view>

namespace sly::gl {
    class ShaderProgram final {
    public:
        enum class Type : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };

    private:
        GLuint program_id;

        [[nodiscard]] static constexpr std::string_view get_name_from_type(Type type);
        [[nodiscard]] std::pair<GLuint, bool> compile(Type type, std::string_view source, bool fallback = false);
        void link_program(GLuint program) const;

    public:
        ShaderProgram(
                std::string_view vertex_source,
                std::string_view geometry_source,
                std::string_view fragment_source
        );
        ShaderProgram(std::string_view vertex_source, std::string_view fragment_source);
        ~ShaderProgram();

        void use();
    };
} // namespace sly::gl
