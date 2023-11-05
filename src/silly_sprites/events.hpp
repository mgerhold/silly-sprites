#include <string>
#include <type_traits>
#include <variant>

namespace sly::event {
    // add new events here
    struct CollisionEvent { };
    struct SoundEvent { };
    struct MessageEvent {
    private:
        std::string m_message;

    public:
        MessageEvent(std::string message) : m_message{ message } { }

        [[nodiscard]] std::string message() const {
            return m_message;
        }
    };

    template<typename T, typename... Ts>
    concept IsAnyOf = std::disjunction_v<std::is_same<T, Ts>...>;
    template<typename... T>
    using VariantCallbacks = std::variant<std::function<void(T const&)>...>;

    template<typename T>
    concept Event = IsAnyOf<T, CollisionEvent, SoundEvent, MessageEvent>;              // add new events here
    using EventCallbacks = VariantCallbacks<CollisionEvent, SoundEvent, MessageEvent>; // add new events here

} // namespace sly::event
