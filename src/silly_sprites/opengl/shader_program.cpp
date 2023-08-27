#include "shader_program.hpp"
#include "utils.hpp"

namespace sly::gl {
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

    [[nodiscard]] ShaderProgram::Shader
    ShaderProgram::compile(Type const type, std::string_view const source, bool const fallback) {
        // compile

        auto id{ glCreateShader(sly::to_underlying(type)) };
        auto const* c_str = source.data();
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

        if (success) {
            return { id };
        } else {
            glDeleteShader(id);
            return {};
        }
    }

    void ShaderProgram::attach_shader(Type const type, Shader const shader) const {
        if (not shader.has_value()) {
            spdlog::error("shader {} not add to program", get_name_from_type(type));
            return;
        }

        glAttachShader(m_program_id, shader.value());
        glDeleteShader(shader.value());
    }

    void ShaderProgram::link_program() const {
        glLinkProgram(m_program_id);

        GLint success;
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
        if (not success) {
            GLchar message[512];
            glGetProgramInfoLog(m_program_id, 512, NULL, message);
            spdlog::critical("ERROR::PROGRAMM::LINK_FAILED -> {}\n", message);
        }
    }

    ShaderProgram::ShaderProgram(
            std::string_view const vertex_source,
            std::string_view const geometry_source,
            std::string_view const fragment_source
    ) {
        m_program_id = { glCreateProgram() };

        auto const vertex_shader = compile(Type::Vertex, vertex_source);
        auto const geometry_shader = compile(Type::Geometry, geometry_source);
        auto const fragment_shader = compile(Type::Fragment, fragment_source);

        attach_shader(Type::Vertex, vertex_shader);
        attach_shader(Type::Geometry, geometry_shader);
        attach_shader(Type::Fragment, fragment_shader);

        link_program();
    }

    ShaderProgram::ShaderProgram(std::string_view const vertex_source, std::string_view const fragment_source) {

        m_program_id = { glCreateProgram() };

        auto const vertex_shader = compile(Type::Vertex, vertex_source);
        auto const fragment_shader = compile(Type::Fragment, fragment_source);

        attach_shader(Type::Vertex, vertex_shader);
        attach_shader(Type::Fragment, fragment_shader);

        link_program();
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program_id);
    }

    void ShaderProgram::use() {
        glUseProgram(m_program_id);
    }

} // namespace sly::gl
