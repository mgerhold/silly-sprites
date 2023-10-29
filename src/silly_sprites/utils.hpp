#pragma once

#include "types.hpp"
#include <filesystem>
#include <string>
#include <tl/optional.hpp>
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

    [[nodiscard]] tl::optional<std::string> read_file(std::filesystem::path const& path);

    template<usize>
    inline constexpr auto dependent_false = false;

    template<typename>
    inline constexpr auto type_dependent_false = false;


    [[nodiscard]] std::string ltrim(std::string s);
    [[nodiscard]] std::string rtrim(std::string s);
    [[nodiscard]] std::string trim(std::string s);

} // namespace sly
