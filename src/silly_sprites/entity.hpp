#pragma once

#include "utils.hpp"
#include <entt/entt.hpp>
#include <iostream>

namespace sly {

    class Entity final {
    public:
        using Identifier = entt::entity;
        using Registry = entt::registry;

    private:
        Identifier m_identifier;
        Registry* m_registry;

    public:
        Entity(Identifier const identifier, Registry* const registry)
            : m_identifier{ identifier },
              m_registry{ registry } { }

        template<typename Component>
        [[nodiscard]] Component& get_component() {
            return m_registry->get<Component>(m_identifier);
        }

        template<typename Component>
        [[nodiscard]] Component const& get_component() const {
            return m_registry->get<Component>(m_identifier);
        }

        template<typename... Components>
        [[nodiscard]] std::tuple<Components&...> get_components() {
            return m_registry->get<Components...>(m_identifier);
        }

        template<typename... Components>
        [[nodiscard]] std::tuple<Components const&...> get_components() const {
            return m_registry->get<Components...>(m_identifier);
        }

        friend std::ostream& operator<<(std::ostream& ostream, const Entity& entity) {
            return ostream << to_underlying(entity.m_identifier);
        }
    };

} // namespace sly
