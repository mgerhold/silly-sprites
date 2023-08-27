#pragma once

#include "app_context.hpp"
#include "native_script.hpp"
#include "script.hpp"
#include "script/engine.hpp"
#include "transform.hpp"
#include "utils.hpp"
#include <entt/entt.hpp>
#include <iostream>
#include <memory>
#include <ranges>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace sly {

    class Scene;

    class GameObject final {
    public:
        using Entity = entt::entity;
        using Registry = entt::registry;

    private:
        Entity m_entity;
        Scene* m_scene;

    public:
        GameObject(Entity const entity, Scene* const scene) : m_entity{ entity }, m_scene{ scene } { }

        template<typename Component>
        [[nodiscard]] Component& get_component();

        template<typename Component>
        [[nodiscard]] Component const& get_component() const;

        template<typename... Components>
        [[nodiscard]] std::tuple<Components&...> get_components();

        template<typename... Components>
        [[nodiscard]] std::tuple<Components const&...> get_components() const;

        template<typename Component>
        void add_component(Component&& component);

        template<typename Component>
        void remove_component();

        template<typename... Components>
        void add_components(Components&&... components) {
            (add_component(std::forward<Components>(components)), ...);
        }

        void destroy();

        explicit operator Entity() const {
            return m_entity;
        }

        friend std::ostream& operator<<(std::ostream& ostream, GameObject const& game_object) {
            auto const integer_value = to_underlying(game_object.m_entity);
            static_assert(sizeof(integer_value) == 4);
            return ostream << fmt::format("{0} (0b{0:032b})", integer_value);
        }

        friend class Scene;
    };
} // namespace sly

template<>
struct fmt::formatter<sly::GameObject> : ostream_formatter { };

#include "scene.inl"

namespace sly {
    template<typename Component>
    [[nodiscard]] Component& GameObject::get_component() {
        return m_scene->m_registry.get<Component>(m_entity);
    }

    template<typename Component>
    [[nodiscard]] Component const& GameObject::get_component() const {
        return m_scene->m_registry.get<Component>(m_entity);
    }

    template<typename... Components>
    [[nodiscard]] std::tuple<Components&...> GameObject::get_components() {
        return m_scene->m_registry.get<Components...>(m_entity);
    }

    template<typename... Components>
    [[nodiscard]] std::tuple<Components const&...> GameObject::get_components() const {
        return m_scene->m_registry.get<Components...>(m_entity);
    }

    template<typename Component>
    void GameObject::add_component(Component&& component) {
        m_scene->m_registry.emplace<Component>(m_entity, std::forward<Component>(component));
    }

    template<typename Component>
    void GameObject::remove_component() {
        m_scene->template remove_component<Component>(*this);
    }

    inline void GameObject::destroy() {
        m_scene->destroy(*this);
    }

} // namespace sly
