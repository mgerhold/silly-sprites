#include "../silly_sprites/include/silly_sprites.hpp"

using namespace sly;

class SandboxApplication final : public sly::Application {
public:
    SandboxApplication() : sly::Application{ sly::ApplicationSettings{} } { }
};



int main() {
    auto application = SandboxApplication{};
    application.run();
}
