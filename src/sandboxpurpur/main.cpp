#include "../silly_sprites/event/events.hpp"
#include "../silly_sprites/include/silly_sprites.hpp"

#include <iostream>

using namespace sly;

class SandboxApplication final : public sly::Application {
public:
    SandboxApplication() : sly::Application{ sly::ApplicationSettings{} } { }
};

class Object : public event::Handler<event::Sound>, public event::Handler<event::Message> {
public:
    Object() {
        event::Sound::connect(this);
    }

    void on_event(event::Sound const& event) override {
        std::cout << this << " | " << event.sound() << '\n';
    }

    void on_event(event::Message const& event) override {
        std::cout << this << " | " << event.message() << '\n';
    }
};


int main() {
    Object first;
    Object second = std::move(first);
    Object third = second;

    event::Message::connect(&third);
    Object fourth = third;
    event::Message::disconnect(&fourth);

    event::Sound s0 = { "jump.wav" };
    event::Sound s1 = { "shoot.wav" };
    event::Message m0 = { "best message" };


    s0.dispatch();
    m0.dispatch();
    s1.dispatch();
}
