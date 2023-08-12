namespace sly {
    class Scene final {
    private:
        entt::registry m_registry;
        std::vector<GameObject::Entity> m_entities_to_destroy;
        std::vector<std::function<void()>> m_component_deleters;

        struct EntityMarker { };
        struct PlaceholderComponent { };

        template<typename EnttViewIterator>
        class ViewWrapper {
        private:
            EnttViewIterator m_begin;
            EnttViewIterator m_end;
            Scene* m_scene;

            class Iterator {
            private:
                EnttViewIterator m_current;
                Scene* m_scene;

            public:
                Iterator(EnttViewIterator current, Scene* scene) : m_current{ current }, m_scene{ scene } { }

                [[nodiscard]] decltype(auto) operator*() {
                    return GameObject{ *m_current, m_scene };
                }

                Iterator& operator++() {
                    ++m_current;
                    return *this;
                }

                Iterator operator++(int) {
                    auto const result = *this;
                    ++(*this);
                    return result;
                }

                [[nodiscard]] bool operator==(Iterator const& other) const {
                    return m_current == other.m_current and m_scene == other.m_scene;
                }
            };

        public:
            ViewWrapper(EnttViewIterator begin, EnttViewIterator end, Scene* scene)
                : m_begin{ begin },
                  m_end{ end },
                  m_scene{ scene } { }

            [[nodiscard]] auto begin() {
                return Iterator{ m_begin, m_scene };
            }

            [[nodiscard]] auto begin() const {
                return Iterator{ m_begin, m_scene };
            }

            [[nodiscard]] auto end() {
                return Iterator{ m_end, m_scene };
            }

            [[nodiscard]] auto end() const {
                return Iterator{ m_end, m_scene };
            }
        };

    public:
        Scene();

        template<typename... Components>
        GameObject instantiate(Components&&... components) {
            auto game_object = GameObject{ m_registry.create(), this };
            if constexpr (sizeof...(Components) > 0) {
                game_object.add_components(std::forward<Components>(components)...);
            }
            return game_object;
        }

        void destroy(GameObject const game_object) {
            m_entities_to_destroy.push_back(static_cast<GameObject::Entity>(game_object));
        }

        template<typename Component>
        void remove_component(GameObject const game_object) {
            m_component_deleters.push_back([game_object]() {
                auto& registry = game_object.m_scene->m_registry;
                registry.template erase<Component>(game_object.m_entity);
            });
        }

        void update_native_scripts(Time const time) {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                auto const game_object = GameObject{ entity, this };
                if (native_script.update) {
                    native_script.update(game_object, time);
                }
            }
        }

        void update(Time const time) {
            update_native_scripts(time);
        }

        void fixed_update_native_scripts(Time const time) {
            auto view = m_registry.view<NativeScript>();
            for (auto [entity, native_script] : view.each()) {
                auto const game_object = GameObject{ entity, this };
                if (native_script.fixed_update) {
                    native_script.fixed_update(game_object, time);
                }
            }
        }

        void fixed_update(Time const time) {
            fixed_update_native_scripts(time);
        }

        void destroy_queued_components() {
            for (auto const& deleter : m_component_deleters) {
                deleter();
            }
            m_component_deleters.clear();
        }

        void destroy_queued_entities() {
            for (auto const entity_to_destroy : m_entities_to_destroy) {
                m_registry.destroy(entity_to_destroy);
            }
            m_entities_to_destroy.clear();
        }

        template<typename... Components>
        [[nodiscard]] auto find_game_objects_with_components() {
            using std::ranges::views::transform;
            auto view = m_registry.template view<Components...>();
            return ViewWrapper{ view.begin(), view.end(), this };
        }

        friend class GameObject;
    };

    Scene::Scene() {
        instantiate(
                Transform{
                        Vec3{ 1.0f, 2.0f, 3.0f },
                        90.0f,
                        Vec2{ 4.0f, 5.0f },
        },
                NativeScript{
                        [](GameObject game_object, Time const time) {
                            // get the transform
                            auto& transform = game_object.get_component<Transform>();

                            // move the game object along the x-axis
                            transform.position.x += static_cast<float>(time.delta) * 2.0f;

                            auto const last_frame_time = static_cast<u64>(time.elapsed - time.delta);
                            auto const current_frame_time = static_cast<u64>(time.elapsed);
                            if (last_frame_time != current_frame_time) {
                                spdlog::info("tick");
                                game_object.m_scene->instantiate(
                                        NativeScript{
                                                [](GameObject, Time) {},
                                                [](GameObject, Time) {},
                                        },
                                        EntityMarker{}, PlaceholderComponent{}
                                );

                                auto game_objects_with_placeholder =
                                        game_object.m_scene
                                                ->template find_game_objects_with_components<PlaceholderComponent>();
                                for (const auto with_placeholder : game_objects_with_placeholder) {
                                    spdlog::info("this entity has the placeholder component: {}", with_placeholder);
                                }

                                if (current_frame_time % 2 == 0) {
                                    for (auto with_placeholder : game_objects_with_placeholder) {
                                        with_placeholder.template remove_component<PlaceholderComponent>();
                                    }
                                }

                                if (current_frame_time % 5 == 0) {
                                    auto game_objects_to_delete =
                                            game_object.m_scene
                                                    ->template find_game_objects_with_components<EntityMarker>();
                                    for (const auto to_delete : game_objects_to_delete) {
                                        spdlog::info("should delete entity {}", to_delete);
                                        to_delete.m_scene->destroy(to_delete);
                                    }
                                }
                            }
                        },
                        []([[maybe_unused]] GameObject game_object, [[maybe_unused]] Time const time) {},
                }
        );
    }
} // namespace sly
