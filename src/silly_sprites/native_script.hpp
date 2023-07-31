#pragma once

#include "entity.hpp"
#include <functional>

namespace sly {

    struct NativeScript final {
        using UpdateFunction = void (*)(Entity, double);
        using FixedUpdateFunction = void (*)(Entity);

        UpdateFunction update;
        FixedUpdateFunction fixed_update;
    };

} // namespace sly
