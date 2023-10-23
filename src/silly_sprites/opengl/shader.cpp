#include "shader.hpp"
#include "error.hpp"
#include "utils.hpp"

namespace sly::gl {

    Shader::Shader(ShaderType type, std::string_view const source) {
        auto const error_message = [&](GLuint id) -> std::string {
            auto len = GLint{};
            glGetShaderiv(
                    id,
                    GL_INFO_LOG_LENGTH,
                    &len
            );      // gets the length of the error message including the null terminator
                    // cast because the gl function needs the signed int and the string ctor expects a unsigned int.
                    // this causes a waring on linux because the sign could chance.
            auto message = std::string(static_cast<usize>(len - 1), ' '); // create a string with a suitable length
            glGetShaderInfoLog(id, len - 1, nullptr, message.data());
            return trim(std::move(message));
        };

        m_name = glCreateShader(sly::to_underlying(type));
        char const* c_source = source.data();
        glShaderSource(m_name, 1, &c_source, nullptr);
        glCompileShader(m_name);

        auto result = GLint{};
        glGetShaderiv(m_name, GL_COMPILE_STATUS, &result);

        if (result == GL_TRUE) {
            m_valid = true;
            spdlog::info("SUCCESS::SHADER::{}::COMPILATION", get_name_from_shader_type(type));
        } else {
            m_valid = false;
            auto const message = error_message(m_name);
            spdlog::critical(
                    "ERROR::SHADER::{}::COMPILATION_FAILED\nerror: {}",
                    get_name_from_shader_type(type),
                    message
            );
        }
    }

    Shader::Shader(Shader&& other) noexcept
        : m_name{ std::exchange(other.m_name, 0) },
          m_valid{ std::exchange(other.m_valid, false) } { }

    Shader& Shader::operator=(Shader&& other) noexcept {
        std::swap(m_name, other.m_name);
        std::swap(m_valid, other.m_valid);
        return *this;
    }

    Shader::~Shader() {
        glDeleteShader(m_name);
    }

    [[nodiscard]] bool Shader::is_valid() const {
        return m_valid;
    }

    [[nodiscard]] GLuint Shader::get_name() const {
        return m_name;
    }

} // namespace sly::gl
