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


        auto const vertex_shader = compile(ShaderType::Vertex, vertex_source);
        if (vertex_shader.is_valid()) {
            glAttachShader(m_program_name, vertex_shader.name());
        }


        if (not geometry_source.empty()) {
            auto const geometry_shader = compile(ShaderType::Geometry, geometry_source);
            if (geometry_shader.is_valid()) {
                glAttachShader(m_program_name, geometry_shader.name());
            }
        }


        auto const fragment_shader = compile(ShaderType::Fragment, fragment_source);
        if (fragment_shader.is_valid()) {
            glAttachShader(m_program_name, fragment_shader.name());
        }

        link_program();
    }

    ShaderProgram::ShaderProgram(std::string_view const vertex_source, std::string_view const fragment_source)
        : ShaderProgram{ vertex_source, "", fragment_source } { }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
        : m_program_name{ std::exchange(other.m_program_name, 0) } { }


    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
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

    [[nodiscard]] Shader ShaderProgram::compile(ShaderType const type, std::string_view const source) {

        auto shader = Shader(type, source);
        if (shader.is_valid()) {
            return shader;
        }

        switch (type) {
            case ShaderType::Vertex: {
                auto fallback_shader = Shader(type, fallback_vertex_source);
                if (fallback_shader.is_valid()) {
                    return fallback_shader;
                }
                throw GlError(GlErrorType::FailedToCompileVertexShader);
            }
            case ShaderType::Geometry:
                /*
                    im not quite sure if i like this.
                    idea is that this is an error but not a error worth it to throw an exception.
                    but in this case i return a invalid shader and the caller has to ask the shader if it is valid.
                    that is inconsistent. but i have no idea how so solve this in a better way.
                */
                spdlog::critical("No fallback for Geometry shader available.");
                return shader;
            case ShaderType::Fragment:
                auto fallback_shader = Shader(type, fallback_fragment_source);
                if (fallback_shader.is_valid()) {
                    return fallback_shader;
                }
                throw GlError(GlErrorType::FailedToCompileVertexShader);
        }
        throw GlError(GlErrorType::InvalidShaderType);
    }

    void ShaderProgram::link_program() const {
        auto const error_message = [&]() -> std::string {
            auto len = GLint{};
            glGetProgramiv(
                    m_program_name,
                    GL_INFO_LOG_LENGTH,
                    &len
            );      // gets the length of the error message including the null terminator
                    // cast beacuse the gl function needs the signed int and the string ctor expects a unsigned int.
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

} // namespace sly::gl
