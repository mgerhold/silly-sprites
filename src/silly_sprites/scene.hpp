#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <spdlog/spdlog.h>
#include <type_traits>

struct NativeScript {
    std::function<void(entt::registry&, entt::entity, double)> update;
    std::function<void(entt::registry&, entt::entity)> fixed_update;
};

class Scene final {
private:
    entt::registry m_registry;

public:
    Scene() {
        auto const entity = m_registry.create();
        m_registry.emplace<NativeScript>(
                entity,
                [](entt::registry&, entt::entity, double const delta_time) {
                    spdlog::info("NativeScript::update({})", delta_time);
                },
                [](entt::registry&, entt::entity) { spdlog::info("NativeScript::fixed_update()"); }
        );
    }

    void update(double const delta_time) {
        auto view = m_registry.view<NativeScript>();
        for (auto [entity, native_script] : view.each()) {
            if (native_script.update) {
                spdlog::info("updating entity {}", static_cast<std::underlying_type_t<decltype(entity)>>(entity));
                native_script.update(m_registry, entity, delta_time);
            }
        }
    }

    void fixed_update() {
        auto view = m_registry.view<NativeScript>();
        for (auto [entity, native_script] : view.each()) {
            if (native_script.fixed_update) {
                spdlog::info("fixed updating entity {}", static_cast<std::underlying_type_t<decltype(entity)>>(entity));
                native_script.fixed_update(m_registry, entity);
            }
        }
    }
};
