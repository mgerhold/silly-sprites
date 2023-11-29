#pragma once

#include "event_concept.hpp"
#include <algorithm>
#include <cassert>
#include <vector>


namespace sly::event {
    template<Event E>
    class Handler {
    public:
        Handler() {
            E::connect(*this);
        };
        Handler(Handler const& other) = delete;
        Handler(Handler&& other) noexcept = delete;
        Handler& operator=(Handler const& other) = delete;
        Handler& operator=(Handler&& other) = delete;

        virtual ~Handler() {
            E::disconnect(*this);
        }

        virtual void on_event(E const& event) = 0;
    };

    template<Event E>
    struct Base {
    private:
        inline static std::vector<Handler<E>*> s_handlers;

        [[nodiscard]] static bool contains_handler(Handler<E> const* handler) {
            return std::find(s_handlers.begin(), s_handlers.end(), handler) != s_handlers.end();
        }

    protected:
        Base() = default;

    public:
        static void connect(Handler<E>& handler) {
            if (contains_handler(&handler)) {
                return;
            }
            s_handlers.push_back(&handler);
        }

        static void disconnect(Handler<E>& handler) {
            std::erase(s_handlers, &handler);
        }

        void dispatch() const {
            for (auto const& h : s_handlers) {
                assert(h != nullptr);
                h->on_event(static_cast<E const&>(*this));
            }
        }
    };
} // namespace sly::event
