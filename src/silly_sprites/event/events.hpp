#pragma once

#include "base_handler.hpp"
#include <string>

namespace sly::event {
    struct Message final : public Base<Message> {
    private:
        std::string m_message;

    public:
        Message(std::string const& message) : m_message{ message } {};

        [[nodiscard]] std::string message() const {
            return m_message;
        }
    };

    struct Sound final : public Base<Sound> {
    private:
        std::string m_sound;

    public:
        Sound(std::string const& sound) : m_sound{ sound } {};

        [[nodiscard]] std::string sound() const {
            return m_sound;
        }
    };
} // namespace sly::event