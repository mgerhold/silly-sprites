#pragma once
#include <glad/gl.h>
#include <string_view>
#include <cassert>

namespace sly::gl {

    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

    [[nodiscard]] constexpr std::string_view get_name_from_shader_type(ShaderType const type) {
        switch (type) {
            case ShaderType::Vertex:
                return "VERTEX";
            case ShaderType::Geometry:
                return "GEOMETRY";
            case ShaderType::Fragment:
                return "FRAGMENT";
        }
        assert(false and "unreachable");
        return "INVALID";
    }

} // namespace sly::gl
