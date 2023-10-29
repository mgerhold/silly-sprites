#include <type_traits>
#include <variant>
#include <functional>

namespace sly::event {
    // add new events here
    struct CollisionEvent { };
    struct SoundEvent { };

    template<typename T, typename... Ts>
    concept IsAnyOf = std::disjunction_v<std::is_same<T, Ts>...>;
    template<typename... T>
    using VariantCallbacks = std::variant<std::function<void(T const&)>...>;

    template<typename T>
    concept Event = IsAnyOf<T, CollisionEvent, SoundEvent>;              // add new events here
    using EventCallbacks = VariantCallbacks<CollisionEvent, SoundEvent>; // add new events here

} // namespace sly::event
