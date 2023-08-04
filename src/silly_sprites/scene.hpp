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
            add_entity(
                    Transform{
                            Vec3{ 1.0f, 2.0f, 3.0f },
                            90.0f,
                            Vec2{ 4.0f, 5.0f },
            },
                    NativeScript{
                            [](Entity entity, double const delta_time) {
                                // get the transform
                                auto& transform = entity.get_component<Transform>();

                                // move the entity along the x-axis
                                transform.position.x += static_cast<float>(delta_time) * 2.0f;

                                // print the current position
                                spdlog::info("NativeScript::update({}), position = {}", delta_time, transform.position);
                            },
                            [](Entity entity) { spdlog::info("NativeScript::fixed_update()"); } }
            );
        }

        template<typename FirstComponent, typename... OtherComponents>
        entt::entity add_entity(FirstComponent&& first_component, OtherComponents&&... other_components) {
            if constexpr (sizeof...(other_components) == 0) {
                auto const entity = m_registry.create();
                m_registry.emplace<FirstComponent>(entity, std::forward<FirstComponent>(first_component));
                return entity;
            } else {
                auto const entity = add_entity(std::forward<OtherComponents>(other_components)...);
                m_registry.emplace<FirstComponent>(entity, std::forward<FirstComponent>(first_component));
                return entity;
            }
        }

        void update(double const delta_time) {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                if (native_script.update) {
                    spdlog::info("updating entity {}", static_cast<std::underlying_type_t<decltype(entity)>>(entity));
                    native_script.update(Entity{ entity, &m_registry }, delta_time);
                }
            }
        }

        void fixed_update() {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                if (native_script.fixed_update) {
                    spdlog::info(
                            "fixed updating entity {}", static_cast<std::underlying_type_t<decltype(entity)>>(entity)
                    );
                    native_script.fixed_update(Entity{ entity, &m_registry });
                }
            }
        }
    };

} // namespace sly
