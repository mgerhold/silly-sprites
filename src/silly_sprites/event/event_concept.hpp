#pragma once

#include <concepts>
#include <type_traits>

namespace sly::event {
    // add Events here
    struct Message;

    template<typename T, typename... Ts>
    concept IsAnyOf = std::disjunction_v<std::is_same<T, Ts>...>;

    template<typename E>
    concept Event = IsAnyOf<E, Message>; // add Events here
} // namespace sly::event
