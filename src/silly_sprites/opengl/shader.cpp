#include "shader.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <gsl/gsl>

namespace sly::gl {

    Shader::Shader(GLuint const name) : m_name{ name } { }

    Shader::Shader(Shader&& other) noexcept : m_name{ std::exchange(other.m_name, 0) } { }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this == std::addressof(other)) {
            return *this;
        }
        std::swap(m_name, other.m_name);
        return *this;
    }

    Shader::~Shader() {
        glDeleteShader(m_name);
    }

    [[nodiscard]] tl::expected<Shader, GlError> Shader::create(ShaderType const type, std::string_view const source) {
        if (source.empty()) {
            spdlog::warn("no shader source");
            return tl::unexpected{ GlError{ GlErrorType::NoShaderSource } };
        }
        auto const trimmed_source = trim(std::string{ source });
        if (trimmed_source.empty()) {
            spdlog::warn("empty shader source");
            return tl::unexpected{ GlError{ GlErrorType::EmptyShaderSource } };
        }
        auto const error_message = [&](GLuint id) -> std::string {
            auto len = GLint{};
            glGetShaderiv(
                    id,
                    GL_INFO_LOG_LENGTH,
                    &len
            );      // gets the length of the error message including the null terminator
                    // cast because the gl function needs the signed int and the string ctor expects a unsigned int.
                    // this causes a warning on linux because the sign could chance.
            auto message = std::string(gsl::narrow_cast<usize>(len - 1), ' '); // create a string with a suitable length
            glGetShaderInfoLog(id, len - 1, nullptr, message.data());
            return trim(std::move(message));
        };

        auto const name = glCreateShader(sly::to_underlying(type));
        if (name == 0) {
            spdlog::critical("Failed to create Shader");
            return tl::unexpected{ GlError{ GlErrorType::FailedToCreateShader } };
        }
        auto const sources = std::array{ source.data() };
        glShaderSource(name, gsl::narrow_cast<GLsizei>(sources.size()), sources.data(), nullptr);
        glCompileShader(name);

        auto result = GLint{};
        glGetShaderiv(name, GL_COMPILE_STATUS, &result);

        if (result != GL_TRUE) {
            auto const message = error_message(name);
            spdlog::critical(
                    "ERROR::SHADER::{}::COMPILATION_FAILED\nerror: {}",
                    get_name_from_shader_type(type),
                    message
            );
            return tl::unexpected{ GlError{ GlErrorType::FailedToCompileShader } };
        }
        spdlog::info("SUCCESS::SHADER::{}::COMPILATION", get_name_from_shader_type(type));
        return { Shader{ name } };
    }

    [[nodiscard]] GLuint Shader::name() const {
        return m_name;
    }

} // namespace sly::gl
