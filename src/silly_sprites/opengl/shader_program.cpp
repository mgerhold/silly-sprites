#include "shader_program.hpp"
#include "error.hpp"
#include "gsl/gsl"
#include "utils.hpp"

namespace sly::gl {
    static constexpr auto fallback_vertex_source = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    static constexpr auto fallback_fragment_source = R"(
            #version 330 core
            out vec4 FragColor;
            
            void main()
            {
                FragColor = vec4(255.0f, 0.0f, 255.0f, 1.0f);
            }  
        )";

    ShaderProgram::ShaderProgram(
            std::string_view const vertex_source,
            std::string_view const geometry_source,
            std::string_view const fragment_source
    ) {
        m_program_name = glCreateProgram();
        if (m_program_name == 0) {
            spdlog::critical("Failed to crate a Shader Program");
            throw GlError(GlErrorType::FailedToCreateShaderProgram);
        }

        auto const vertex_shader = Shader::create(ShaderType::Vertex, vertex_source)
                                           .or_else([]([[maybe_unused]] auto error) {
                                               spdlog::info("using default vertex shader");
                                               return Shader::create(ShaderType::Vertex, fallback_vertex_source);
                                           })
                                           .value();
        glAttachShader(m_program_name, vertex_shader.name());

        auto const geometry_shader = Shader::create(ShaderType::Geometry, geometry_source);
        if (geometry_shader.has_value()) {
            glAttachShader(m_program_name, geometry_shader.value().name());
        } else {
            spdlog::warn("ignoring geometry shader (compilation failed)");
        }

        auto const fragment_shader = Shader::create(ShaderType::Fragment, fragment_source)
                                             .or_else([]([[maybe_unused]] auto error) {
                                                 spdlog::info("using default fragment shader");
                                                 return Shader::create(ShaderType::Fragment, fallback_fragment_source);
                                             })
                                             .value();
        glAttachShader(m_program_name, fragment_shader.name());

        auto const error_message = [&]() -> std::string {
            auto len = GLint{};
            glGetProgramiv(
                    m_program_name,
                    GL_INFO_LOG_LENGTH,
                    &len
            );      // gets the length of the error message including the null terminator
                    // cast because the gl function needs the signed int and the string ctor expects a unsigned int.
                    // this causes a waring on linux because the sign could chance.
            auto message = std::string(static_cast<usize>(len - 1), ' '); // create a string with a suitable length
            glGetProgramInfoLog(m_program_name, len - 1, nullptr, message.data());
            return trim(message);
        };

        glLinkProgram(m_program_name);

        GLint success;
        glGetProgramiv(m_program_name, GL_LINK_STATUS, &success);
        if (not success) {
            auto const message = error_message();
            spdlog::critical("ERROR::PROGRAMM::LINK_FAILED -> {}\n", message.data());
            glDeleteProgram(m_program_name);
            throw GlError(GlErrorType::FailedToLinkShaderProgram, message);
        }
    }

    ShaderProgram::ShaderProgram(std::string_view const vertex_source, std::string_view const fragment_source)
        : ShaderProgram{ vertex_source, "", fragment_source } { }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
        : m_program_name{ std::exchange(other.m_program_name, 0) } { }


    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
        if (this == std::addressof(other)) {
            return *this;
        }

        std::swap(m_program_name, other.m_program_name);
        return *this;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program_name);
    }


    void ShaderProgram::bind() {
        glUseProgram(m_program_name);
    }

    void ShaderProgram::unbind() {
        glUseProgram(0);
    }
} // namespace sly::gl
