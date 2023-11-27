#pragma once

#include <type_traits>
#include <concepts>

namespace sly::event {
    // add Events here
    struct Message;
    struct Sound;

    template<typename T, typename... Ts>
    concept IsAnyOf = std::disjunction_v<std::is_same<T, Ts>...>;

    template<typename E>
    concept Event = IsAnyOf<E, Message, Sound>; // add Events here
} // namespace sly::event
