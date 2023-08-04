#pragma once

#include "utils.hpp"
#include <entt/entt.hpp>
#include <iostream>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace sly {

    class GameObject final {
    public:
        using Entity = entt::entity;
        using Registry = entt::registry;

    private:
        Entity m_entity;
        Registry* m_registry;

    public:
        GameObject(Entity const entity, Registry* const registry) : m_entity{ entity }, m_registry{ registry } { }

        template<typename Component>
        [[nodiscard]] Component& get_component() {
            return m_registry->get<Component>(m_entity);
        }

        template<typename Component>
        [[nodiscard]] Component const& get_component() const {
            return m_registry->get<Component>(m_entity);
        }

        template<typename... Components>
        [[nodiscard]] std::tuple<Components&...> get_components() {
            return m_registry->get<Components...>(m_entity);
        }

        template<typename... Components>
        [[nodiscard]] std::tuple<Components const&...> get_components() const {
            return m_registry->get<Components...>(m_entity);
        }

        explicit operator Entity() const {
            return m_entity;
        }

        friend std::ostream& operator<<(std::ostream& ostream, GameObject const& game_object) {
            return ostream << to_underlying(game_object.m_entity);
        }
    };

} // namespace sly

template<>
struct fmt::formatter<sly::GameObject> : ostream_formatter { };
