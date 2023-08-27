#pragma once

#include "script/object.hpp"
#include <string>
#include <tl/optional.hpp>

namespace sly {

    struct Script {
        std::string class_name;
        tl::optional<script::Object> instance{ tl::nullopt };

    public:
        explicit Script(std::string class_name) : class_name{ std::move(class_name) } { }
    };

} // namespace sly
