#include "shader_program.hpp"
#include "utils.hpp"

namespace sly::gl {
    [[nodiscard]] constexpr std::string_view ShaderProgram::get_name_from_type(Type const type) {
        switch (type) {
            case Type::Vertex:
                return "VERTEX";
            case Type::Geometry:
                return "GEOMETRY";
            case Type::Fragment:
                return "FRAGMENT";
            default:
                return "INVALID";
        }
    }

    std::pair<GLuint, bool> ShaderProgram::compile(Type const type, std::string_view source, bool fallback) {
        // compile

        auto id{ glCreateShader(sly::to_underlying(type)) };
        char const* c_str = source.data();
        glShaderSource(id, 1, &c_str, nullptr);
        glCompileShader(id);

        // check
        GLint success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (not success) {
            GLchar message[512];
            glGetShaderInfoLog(id, 512, nullptr, message);
            spdlog::critical("ERROR::SHADER::{}::COMPILATION_FAILED -> {}", get_name_from_type(type), message);

            if (not fallback) {
                if (type != Type::Geometry) {
                    glDeleteShader(id);
                    spdlog::error("ERROR::SHADER::{}::FALLBACK", get_name_from_type(type));
                    if (type == Type::Vertex) {
                        return compile(type, fallback_vertex_source, true);
                    } else { // Type::Fragment
                        return compile(type, fallback_fragment_source, true);
                    }
                } else {
                    spdlog::critical("ERRPR::SHADER::{}::NO_FALLBACK", get_name_from_type(type));
                }
            }

        } else {
            spdlog::info("SUCCESS::SHADER::{}::COMPILATION", get_name_from_type(type));
        }

        return { id, success };
    }

    void ShaderProgram::link_program(GLuint program) const {
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (not success) {
            GLchar message[512];
            glGetProgramInfoLog(program, 512, NULL, message);
            spdlog::critical("ERROR::PROGRAMM::LINK_FAILED -> {}\n", message);
        }
    }

    ShaderProgram::ShaderProgram(
            std::string_view vertex_source,
            std::string_view geometry_source,
            std::string_view fragment_source
    ) {
        auto const [vertex_id, _]{ compile(Type::Vertex, vertex_source) };
        auto const [geometry_id, success]{ compile(Type::Geometry, geometry_source) };
        auto const [fragment_id, __]{ compile(Type::Fragment, fragment_source) };

        program_id = { glCreateProgram() };
        glAttachShader(program_id, vertex_id);
        glAttachShader(program_id, fragment_id);
        if (success) {
            glAttachShader(program_id, geometry_id);
        } else {
            spdlog::error("geometry shader not add to program");
        }

        link_program(program_id);

        glDeleteShader(vertex_id);
        glDeleteShader(geometry_id);
        glDeleteShader(fragment_id);
    }

    ShaderProgram::ShaderProgram(std::string_view vertex_source, std::string_view fragment_source) {
        auto const [vertex_id, _]{ compile(Type::Vertex, vertex_source) };
        auto const [fragment_id, __]{ compile(Type::Fragment, fragment_source) };

        program_id = { glCreateProgram() };
        glAttachShader(program_id, vertex_id);
        glAttachShader(program_id, fragment_id);

        link_program(program_id);

        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(program_id);
    }

    void ShaderProgram::set_active() {
        glUseProgram(program_id);
    }

} // namespace sly::gl
