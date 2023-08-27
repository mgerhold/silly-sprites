namespace sly {
    class Scene final {
    private:
        AppContext* m_app_context;
        entt::registry m_registry;
        std::vector<GameObject::Entity> m_entities_to_destroy;
        std::vector<std::function<void()>> m_component_deleters;

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
        Scene(AppContext* app_context);
        Scene(Scene const&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(Scene const&) = delete;
        Scene& operator=(Scene&&) = delete;
        ~Scene();

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

        void update_scripts(Time const time) {
            using script::builtins::ExecutionContext;
            using script::builtins::g_current_script_execution_context;

            auto& script_engine = m_app_context->script_engine();
            m_registry.view<Script>().each([&](auto entity, Script& script) {
                auto game_object = GameObject{ entity, this };
                assert(not g_current_script_execution_context.has_value());
                g_current_script_execution_context = ExecutionContext{ &game_object };
                if (not script.instance.has_value()) {
                    spdlog::info("spawning object of type '{}'", script.class_name);
                    script.instance = script_engine.create_object(script.class_name);
                    auto const awake_method = script_engine.get_class_method(script.class_name, "void awake()");
                    if (awake_method.has_value()) {
                        script_engine.call_method(*script.instance, *awake_method);
                    }
                } else {
                    auto const update_method = script_engine.get_class_method(script.class_name, "void update(Time)");
                    if (update_method.has_value()) {
                        script_engine.call_method(*script.instance, *update_method, time);
                    }
                }
                g_current_script_execution_context = tl::nullopt;
            });
        }

        void update(Time const time) {
            update_native_scripts(time);
            update_scripts(time);
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

    private:
        void on_script_destroyed(GameObject::Registry&, GameObject::Entity entity) {
            auto game_object = GameObject{ entity, this };
            auto script = game_object.get_component<Script>();
            assert(script.instance.has_value());
            spdlog::info("destroying script object for class '{}'", script.class_name);
            m_app_context->script_engine().destroy_object(*script.instance);
        }

        friend class GameObject;
    };

    inline Scene::Scene(AppContext* const app_context) : m_app_context{ app_context } {
        m_registry.on_destroy<Script>().connect<&Scene::on_script_destroyed>(*this);
        instantiate(Script{ "Player" });
        instantiate(Script{ "Player" });
    }

    inline Scene::~Scene() {
        m_registry.on_destroy<Script>().disconnect<&Scene::on_script_destroyed>(*this);
    }
} // namespace sly
