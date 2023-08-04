#pragma once

#include "types.hpp"

namespace sly {

    struct Transform final {
        Vec3 position;
        float rotation;
        Vec2 scale;
    };

} // namespace sly
