#pragma once

#include "../types.hpp"
#include "magic_enum_wrapper.hpp"
#include "shader_type.hpp"
#include "shader.hpp"
#include <tl/optional.hpp>

namespace sly::gl {
    class ShaderProgram final {
    private:
        GLuint m_program_name = 0;

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

        void bind();
        void unbind();
    };
} // namespace sly::gl
