#pragma once

#include "base_handler.hpp"
#include <string>

namespace sly::event {
    struct Message final : public Base<Message> {
    private:
        std::string m_message;

    public:
        explicit Message(std::string message) : m_message{ std::move(message) } {};

        [[nodiscard]] std::string message() const {
            return m_message;
        }
    };
} // namespace sly::event
