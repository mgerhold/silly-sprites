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
        event::Sound::connect(this); // connect event in ctor to proof that.
    }

    void on_event(event::Sound const& event) override {
        std::cout << this << " | " << event.sound() << '\n';
    }

    void on_event(event::Message const& event) override {
        std::cout << this << " | " << event.message() << '\n';
    }
};


int main() {
    auto app = SandboxApplication{};

    Object first;  // sound event from ctor.
    event::Message::connect(&first);

    auto s0 = event::Sound{ "jump.wav" };
    auto s1 = event::Sound{ "shoot.wav" };
    auto m0 = event::Message{ "best message" };


    s0.dispatch();
    
    app.run();

    m0.dispatch();
    s1.dispatch();
}
