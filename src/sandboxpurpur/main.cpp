#define GLFW_INCLUDE_NONE

#include "../silly_sprites/event_system.hpp"
#include "../silly_sprites/include/silly_sprites.hpp"

using namespace sly;

class SandboxApplication final : public sly::Application {
public:
    SandboxApplication() : sly::Application{ sly::ApplicationSettings{} } { }
};

class Test final {
private:
    event::EvenHandlerId m_message_event;
    event::EvenHandlerId m_test_event;
    SandboxApplication& m_app;

public:
    Test(SandboxApplication& app) : m_app{ app } {
        m_message_event = app.event_system().add_handler<event::MessageEvent>([this](event::MessageEvent const& event) {
            this->on_event(event);
        });
    }

    ~Test() {
        // m_app.event_system().remove_handler(m_message_event);
        m_app.event_system().remove_handler(m_test_event);
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
