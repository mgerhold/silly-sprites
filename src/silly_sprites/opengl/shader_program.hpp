#pragma once

#include "../types.hpp"
#include "magic_enum_wrapper.hpp"
#include <glad/gl.h>
#include <string_view>

namespace sly::gl {
    class ShaderProgram {
    public:
        enum class Type : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Geometry = GL_GEOMETRY_SHADER,
            Fragment = GL_FRAGMENT_SHADER,
        };

    private:
        static constexpr char const* fallback_vertex_source{ R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )" };
        static constexpr char const* fallback_fragment_source{ R"(
        #version 330 core
        out vec4 FragColor;
        
        void main()
        {
            FragColor = vec4(255.0f, 0.0f, 255.0f, 1.0f);
        }    
    )" };

        GLuint program_id;

        GLuint compile(Type type, std::string_view source, bool fallback = false);
        void link_program(GLuint program) const;

    public:
        ShaderProgram(
                std::string_view vertex_source,
                std::string_view geometry_source,
                std::string_view fragment_source
        );
        ShaderProgram(std::string_view vertex_source, std::string_view fragment_source);
        ~ShaderProgram();

        void set_active();
    };
} // namespace sly::gl
