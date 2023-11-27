#pragma once

#include "event_concept.hpp"
#include <algorithm>
#include <vector>


namespace sly::event {
    template<Event E>
    class Handler {
    private:
        using handler_ty = Handler<E>;

    public:
        Handler() = default;
        Handler(handler_ty const& other) {
            E::copy(&other, this);
        }
        Handler(handler_ty&& other) noexcept {
            E::move(&other, this);
        }
        handler_ty& operator=(handler_ty const& other) {
            E::copy(&other, this);
        }
        handler_ty& operator=(handler_ty&& other) {
            E::move(&other, this);
        }

        virtual ~Handler() {
            E::disconnect(this);
        }

        virtual void on_event(E const& event) = 0;
    };

    template<Event E>
    struct Base {
    private:
        using handler_ty = Handler<E>*;
        using handler_const_ty = Handler<E> const*;
        inline static std::vector<handler_ty> m_handlers;

        [[nodiscard]] static bool contains_handler(handler_const_ty handler) {
            return std::find(m_handlers.begin(), m_handlers.end(), handler) != m_handlers.end();
        }

        [[nodiscard]] constexpr E& derived() noexcept {
            static_assert(std::derived_from<E, Base>);
            return static_cast<E&>(*this);
        }

    protected:
        Base() = default;

    public:
        static void connect(handler_ty handler) {
            if (contains_handler(handler)) {
                return;
            }
            m_handlers.push_back(handler);
        }
        static void disconnect(handler_ty handler) {
            std::erase(m_handlers, handler);
        }

        static void move(handler_ty from, handler_ty to) {
            for (auto& h : m_handlers) {
                if (h == from) {
                    h = to;
                }
            }
        }
        static void copy(handler_const_ty from, handler_ty to) {
            if (contains_handler(from)) {
                connect(to);
            }
        }


        void dispatch() const {
            for (auto const& h : m_handlers) {
                h->on_event(derived());
            }
        }


        static void dispatch(E event) {
            for (auto const& h : m_handlers) {
                h->on_event(event);
            }
        }
    };
} // namespace sly::event

/*
event::Message::dispatch(event::Message{ "best message" });
event::Message{ "best message" }; // ctor dispatched automatisch
event::Message{ "best message" }.dispatch();
*/
