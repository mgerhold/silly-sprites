#pragma once

#include "native_script.hpp"
#include "transform.hpp"
#include "types.hpp"
#include <entt/entt.hpp>
#include <functional>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <type_traits>

namespace sly {

    class Scene final {
    private:
        using Registry = entt::registry;

        Registry m_registry;

    public:
        Scene() {
            instantiate(
                    Transform{
                            Vec3{ 1.0f, 2.0f, 3.0f },
                            90.0f,
                            Vec2{ 4.0f, 5.0f },
            },
                    NativeScript{
                            [](GameObject game_object, double const delta_time) {
                                // get the transform
                                auto& transform = game_object.get_component<Transform>();

                                // move the game object along the x-axis
                                transform.position.x += static_cast<float>(delta_time) * 2.0f;

                                // print the current position
                                spdlog::info("NativeScript::update({}), position = {}", delta_time, transform.position);
                            },
                            []([[maybe_unused]] GameObject game_object) {
                                spdlog::info("NativeScript::fixed_update()");
                            } }
            );
        }

        GameObject instantiate(auto&&... components) {
            auto game_object = GameObject{ m_registry.create(), &m_registry };
            if constexpr (sizeof...(components) > 0) {
                game_object.add_components(std::forward<decltype(components)>(components)...);
            }
            return game_object;
        }

        void update(double const delta_time) {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                const auto game_object = GameObject{ entity, &m_registry };
                if (native_script.update) {
                    spdlog::info("updating entity {}", game_object);
                    native_script.update(game_object, delta_time);
                }
            }
        }

        void fixed_update() {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                const auto game_object = GameObject{ entity, &m_registry };
                if (native_script.fixed_update) {
                    spdlog::info("fixed updating entity {}", game_object);
                    native_script.fixed_update(game_object);
                }
            }
        }
    };

} // namespace sly
