#pragma once

#include <type_traits>

namespace sly {

    /**
     * This is an implementation of std::to_underlying which is available in C++23 (which we cannot use).
     * @tparam Enum The type of the passed enum value.
     * @tparam Underlying The underlying type of the enum.
     * @param enum_value The enum value.
     * @return The value converted to its underlying type.
     */
    template<typename Enum, typename Underlying = std::underlying_type_t<std::remove_cvref_t<Enum>>>
    [[nodiscard]] Underlying to_underlying(Enum enum_value) {
        return static_cast<Underlying>(enum_value);
    }

} // namespace sly
