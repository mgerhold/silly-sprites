#include "shader_type.hpp"

namespace sly::gl {
    [[nodiscard]] std::string_view get_name_from_shader_type(ShaderType const type) {
        switch (type) {
            case ShaderType::Vertex:
                return "VERTEX";
            case ShaderType::Geometry:
                return "GEOMETRY";
            case ShaderType::Fragment:
                return "FRAGMENT";
        }
        return "INVALID";
    }
} // namespace sly::gl
