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
    event::EventHandlerId m_message_event_2;

public:
    Test(SandboxApplication& app) {
        m_message_event = app.event_system().add_handler<event::MessageEvent>([this](auto const& event) {
            this->on_event(event);
        });
        m_message_event_2 = app.event_system().add_handler<event::SoundEvent>([this](auto const& event) {
            this->on_event_2(event);
        });
    }

    void on_event(event::MessageEvent const& e) {
        spdlog::info("Message Event: {}", e.message());
    }

    void on_event_2(event::SoundEvent const& e) {
        static auto count{ 1 };
        spdlog::info("send {} times", count);
        if (count >= 10) {
            m_message_event_2.remove();
        }
        ++count;
    }
};


int main() {
    auto application = SandboxApplication{};
    auto test = Test{ application };
    application.event_system().dispatch(event::MessageEvent{ "start application" });
    for (int i = 0; i < 20; ++i) {
        application.event_system().dispatch(event::SoundEvent{});
    }
    application.run();
    application.event_system().dispatch(event::MessageEvent{ "end application" });
}
