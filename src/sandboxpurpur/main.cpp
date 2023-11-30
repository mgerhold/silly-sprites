#include "../silly_sprites/event/events.hpp"
#include "../silly_sprites/include/silly_sprites.hpp"

#include <iostream>

using namespace sly;

class SandboxApplication final : public sly::Application {
public:
    SandboxApplication() : sly::Application{ sly::ApplicationSettings{} } { }
};

class Object :  public event::Handler<event::Message> {
public:
    void on_event(event::Message const& event) override {
        std::cout << this << " | " << event.message() << '\n';
    }
};


int main() {
    auto app = SandboxApplication{};

    Object first;

    auto m0 = event::Message{ "best message" };
    
    app.run();

    m0.dispatch();
}
