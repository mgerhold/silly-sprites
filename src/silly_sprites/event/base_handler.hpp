#pragma once

#include "event_concept.hpp"
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <spdlog/spdlog.h>


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
        inline static std::unordered_set<Handler<E>*> s_handlers;

    protected:
        Base() = default;

    public:
        static void connect(Handler<E>& handler) {
            auto const&& [interator, inserted] = s_handlers.insert(&handler);
            if (not inserted) {
                spdlog::warn("handler and event already connected -> ignoring the connect()");
            }
        }

        static void disconnect(Handler<E>& handler) {
            s_handlers.erase(&handler);
        }

        void dispatch() const {
            for (auto const& h : s_handlers) {
                assert(h != nullptr);
                h->on_event(static_cast<E const&>(*this));
            }
        }
    };
} // namespace sly::event
