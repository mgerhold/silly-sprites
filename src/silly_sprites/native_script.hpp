#pragma once

#include "time.hpp"
#include <functional>

namespace sly {

    class GameObject;

    struct NativeScript final {
        using UpdateFunction = void (*)(GameObject, Time);
        using FixedUpdateFunction = void (*)(GameObject, Time);

        UpdateFunction update;
        FixedUpdateFunction fixed_update;
    };

} // namespace sly
