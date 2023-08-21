#pragma once

#include "script/object.hpp"
#include <string>
#include <tl/optional.hpp>

namespace sly {

    struct Script {
        std::string class_name{ "Player" };
        tl::optional<script::Object> instance;
    };

} // namespace sly
