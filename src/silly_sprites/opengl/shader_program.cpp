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

    [[nodiscard]] constexpr std::string_view ShaderProgram::get_name_from_type(Type const type) {
        switch (type) {
            case Type::Vertex:
                return "VERTEX";
            case Type::Geometry:
                return "GEOMETRY";
            case Type::Fragment:
                return "FRAGMENT";
        }
        return "INVALID";
    }

    [[nodiscard]] GLuint ShaderProgram::compile(Type const type, std::string_view const source) {
        // compile

        auto error_message = [&](GLuint id) -> std::string {
            auto message = std::string{};
            auto len = GLint{};
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            message.resize(gsl::narrow_cast<usize>(len - 2));
            glGetShaderInfoLog(id, len - 1, nullptr, message.data());
            return message;
        };
        auto compile_single = [&](GLuint& id, char const* single_source) -> GLint {
            id = glCreateShader(sly::to_underlying(type));
            glShaderSource(id, 1, &single_source, nullptr);
            glCompileShader(id);
            auto success = GLint{};
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            return success;
        };

        auto id = GLuint{};
        auto success = compile_single(id, source.data());

        if (not success) {

            auto message = error_message(id);
            spdlog::critical("ERROR::SHADER::{}::COMPILATION_FAILED\nerror: {}", get_name_from_type(type), message);
            glDeleteShader(id);

            spdlog::info("SHADER::{}::TRY_FALLBACK_COMPILATION", get_name_from_type(type));
            switch (type) {
                case Type::Vertex:
                    success = compile_single(id, fallback_vertex_source);
                    if (not success) {
                        auto message2 = error_message(id);
                        spdlog::critical(
                                "ERROR::SHADER::{}::COMPILATION_FAILED\nerror: {}",
                                get_name_from_type(type),
                                message2
                        );
                        glDeleteShader(id);
                        throw GLError(
                                GLErrorType::FailedToCompileVertexShader,
                                fmt::format("first error: {}\nsecond error: {}", message, message2)
                        );
                    }
                    break;

                case Type::Geometry:
                    spdlog::critical("ERROR::SHADER::{}::NO_FALLBACK", get_name_from_type(type));
                    throw GLError(GLErrorType::FailedToCompileGeometryShader, message);
                    break;

                case Type::Fragment:
                    success = compile_single(id, fallback_fragment_source);
                    if (not success) {
                        auto message2 = error_message(id);
                        spdlog::critical(
                                "ERROR::SHADER::{}::COMPILATION_FAILED\nerror: {}",
                                get_name_from_type(type),
                                message2
                        );
                        glDeleteShader(id);
                        throw GLError(
                                GLErrorType::FailedToCompileVertexShader,
                                fmt::format("first error: {}\nsecond error: {}", message, message2)
                        );
                    }
                    break;
            }
        }

        spdlog::info("SUCCESS::SHADER::{}::COMPILATION", get_name_from_type(type));
        return id;
    }

    void ShaderProgram::attach_shader(GLuint const shader) const {
        glAttachShader(m_program_name, shader);
        glDeleteShader(shader);
    }

    void ShaderProgram::link_program() const {
        glLinkProgram(m_program_name);

        GLint success;
        glGetProgramiv(m_program_name, GL_LINK_STATUS, &success);
        if (not success) {
            auto message = std::string{};
            GLint len;
            glGetProgramiv(m_program_name, GL_INFO_LOG_LENGTH, &len);
            message.resize(gsl::narrow<usize>(len - 2));
            glGetProgramInfoLog(m_program_name, len - 1, nullptr, message.data());
            spdlog::critical("ERROR::PROGRAMM::LINK_FAILED -> {}\n", message.data());
            glDeleteProgram(m_program_name);
            throw GLError(GLErrorType::FailedToLinkShaderProgram, message);
        }
    }

    ShaderProgram::ShaderProgram(
            std::string_view const vertex_source,
            std::string_view const geometry_source,
            std::string_view const fragment_source
    )
        : m_program_name{ 0 } {
        m_program_name = { glCreateProgram() };


        auto const vertex_shader = compile(Type::Vertex, vertex_source);
        attach_shader(vertex_shader);

        if (not geometry_source.empty()) {
            auto const geometry_shader = compile(Type::Geometry, geometry_source);
            attach_shader(geometry_shader);
        }

        auto const fragment_shader = compile(Type::Fragment, fragment_source);
        attach_shader(fragment_shader);

        link_program();
    }

    ShaderProgram::ShaderProgram(std::string_view const vertex_source, std::string_view const fragment_source)
        : ShaderProgram(vertex_source, "", fragment_source) { }

    ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
        : m_program_name{ std::exchange(other.m_program_name, 0) } { }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
        std::swap(m_program_name, other.m_program_name);
        return *this;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_program_name);
    }


    void ShaderProgram::use() {
        glUseProgram(m_program_name);
    }

} // namespace sly::gl
