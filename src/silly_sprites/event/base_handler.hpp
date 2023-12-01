// FAIL!

#pragma once

#include "event_concept.hpp"
#include <algorithm>
#include <cassert>
#include <vector>


namespace sly::event {
    template<Event E>
    class Handler {
    public:
        Handler() = default;
        Handler(Handler const& other) {
            E::copy(&other, this);
        }
        Handler(Handler&& other) noexcept {
            E::move(&other, this);
        }
        Handler& operator=(Handler const& other) {
            if (this == &other) {
                return *this;
            }
            E::copy(&other, this);
            return *this;
        }
        Handler& operator=(Handler&& other) {
            if (this == &other) {
                return *this;
            }
            E::move(&other, this);
            return *this;
        }

        virtual ~Handler() {
            E::disconnect(this);
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
        static void connect(Handler<E>* handler) {
            if (contains_handler(handler)) {
                return;
            }
            s_handlers.push_back(handler);
        }

        static void disconnect(Handler<E>* handler) {
            std::erase(s_handlers, handler);
        }

        static void move(Handler<E>* from, Handler<E>* to) {
            for (auto& h : s_handlers) {
                if (h == from) {
                    h = to;
                }
            }
        }

        static void copy(Handler<E> const* from, Handler<E>* to) {
            if (contains_handler(from)) {
                connect(to);
            }
        }

        void dispatch() const {
            for (auto const& h : s_handlers) {
                assert(h != nullptr);
                h->on_event(static_cast<E const&>(*this));
            }
        }
    };
} // namespace sly::event
