#pragma once
#include <glad/gl.h>
#include <string_view>

namespace sly::gl {

    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

    [[nodiscard]] std::string_view get_name_from_shader_type(ShaderType const type);

} // namespace sly::gl
