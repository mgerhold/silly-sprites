#include "../silly_sprites/event_system.hpp"
#include "../silly_sprites/include/silly_sprites.hpp"

using namespace sly;

class SandboxApplication final : public sly::Application {
public:
    SandboxApplication() : sly::Application{ sly::ApplicationSettings{} } { }
};

class Test final {
private:
    event::EventHandlerId m_message_event;

public:
    Test(SandboxApplication& app) {
        m_message_event = app.event_system().add_handler<event::MessageEvent>([this](auto const& event) {
            this->on_event(event);
        });
    }

    void on_event(event::MessageEvent const& e) {
        spdlog::info("Message Event: {}", e.message());
    }
};


int main() {
    auto application = SandboxApplication{};
    auto test = Test{ application };
    application.event_system().dispatch(event::MessageEvent{ "start application" });
    application.run();
    application.event_system().dispatch(event::MessageEvent{ "end application" });
}
