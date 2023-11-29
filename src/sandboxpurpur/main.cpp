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

    Object first;  // sound event from ctor (first instance).
    Object second = std::move(first); // sound event gets moved (second instance) 
    Object third = second; // sound event gets copied. there are 2 instances now so there are two pointer in the sound event (second & third instance)

    event::Message::connect(&third); // connect message event to the third instance.
    Object fourth = third; // copy of sound and message event.
    event::Message::disconnect(&fourth); // remove message event from fourth (copied) instance. 

    auto s0 = event::Sound{ "jump.wav" };
    auto s1 = event::Sound{ "shoot.wav" };
    auto m0 = event::Message{ "best message" };


    s0.dispatch(); // should be send to instance 2,3,4
    
    app.run();

    m0.dispatch(); // should be send to instance 3
    s1.dispatch(); // should be send to instance 2,3,4
    // instance 1 was moved so all of its pointer were removed.
}
