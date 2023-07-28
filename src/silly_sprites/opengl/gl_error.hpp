#pragma once

#include <string>

namespace sly::gl {

    enum class GlError {
        FailedToInitializeGlfw,
        UnableToCreateGlfwContext,
        FailedToCreateWindow,
        FailedToInitializeGlad,
    };

} // namespace sly::gl
