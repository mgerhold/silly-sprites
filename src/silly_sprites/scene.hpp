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
        entt::registry m_registry;

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

        template<typename FirstComponent, typename... OtherComponents>
        GameObject instantiate(FirstComponent&& first_component, OtherComponents&&... other_components) {
            if constexpr (sizeof...(other_components) == 0) {
                const auto game_object = instantiate();
                m_registry.emplace<FirstComponent>(
                        static_cast<GameObject::Entity>(game_object), std::forward<FirstComponent>(first_component)
                );
                return GameObject{ static_cast<GameObject::Entity>(game_object), &m_registry };
            } else {
                auto const game_object = instantiate(std::forward<OtherComponents>(other_components)...);
                m_registry.emplace<FirstComponent>(
                        static_cast<GameObject::Entity>(game_object), std::forward<FirstComponent>(first_component)
                );
                return GameObject{ static_cast<GameObject::Entity>(game_object), &m_registry };
            }
        }

        GameObject instantiate() {
            return GameObject{ m_registry.create(), &m_registry };
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
