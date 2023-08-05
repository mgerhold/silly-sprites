#pragma once

#include "game_object.hpp"
#include <functional>

namespace sly {

    struct NativeScript final {
        using UpdateFunction = void (*)(GameObject, double);
        using FixedUpdateFunction = void (*)(GameObject);

        UpdateFunction update;
        FixedUpdateFunction fixed_update;
    };

} // namespace sly
