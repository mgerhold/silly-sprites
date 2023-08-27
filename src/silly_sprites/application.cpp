#include "application.hpp"
#include "game_object_and_scene.hpp"
#include "script/engine.hpp"
#include <string>

namespace sly {

    Application::Application(ApplicationSettings settings)
        : m_settings{ settings },
          m_script_engine{ std::make_unique<script::Engine>() } {
        m_script_engine->create_module("MyModule", "src/silly_sprites/test.as");
        m_scenes.push_back(std::make_unique<Scene>(this));
    }

    Application::~Application() = default;

    void Application::run() {
        auto is_running = true;
        m_stopwatch.reset();

        auto last_fixed_update = m_stopwatch.elapsed_time();
        auto last_update = m_stopwatch.elapsed_time();
        auto num_fixed_updates = 0_u64;

        while (is_running) {
            auto elapsed_since_last_fixed_update = m_stopwatch.elapsed_time() - last_fixed_update;
            while (elapsed_since_last_fixed_update >= s_fixed_update_interval) {
                auto const elapsed_time = static_cast<double>(num_fixed_updates) * s_fixed_update_interval;
                fixed_update(Time{ elapsed_time, s_fixed_update_interval });
                process_queued_scene_tasks();
                last_fixed_update += s_fixed_update_interval;
                elapsed_since_last_fixed_update = m_stopwatch.elapsed_time() - last_fixed_update;
                ++num_fixed_updates;
            }

            if (std::holds_alternative<refresh_rate::Unlimited>(m_settings.refresh_rate)
                or std::holds_alternative<refresh_rate::VSync>(m_settings.refresh_rate)) {
                auto const delta_time = m_stopwatch.elapsed_time() - last_update;
                last_update = m_stopwatch.elapsed_time();
                update(Time{ m_stopwatch.elapsed_time(), delta_time });
                process_queued_scene_tasks();
                render();
            } else if (std::holds_alternative<refresh_rate::Limited>(m_settings.refresh_rate)) {
                auto const refresh_rate = std::get<refresh_rate::Limited>(m_settings.refresh_rate).limit;
                auto const elapsed_since_last_update = m_stopwatch.elapsed_time() - last_update;
                if (elapsed_since_last_update >= 1.0 / refresh_rate) {
                    last_update = m_stopwatch.elapsed_time();
                    update(Time{ m_stopwatch.elapsed_time(), elapsed_since_last_update });
                    process_queued_scene_tasks();
                    render();
                }
            }
        }
    }

    void Application::fixed_update(Time const time) {
        for (auto& scene : m_scenes) {
            scene->fixed_update(time);
        }
    }

    void Application::update(Time const time) {
        for (auto& scene : m_scenes) {
            scene->update(time);
        }
    }

    void Application::render() const { }

    void Application::process_queued_scene_tasks() {
        for (auto& scene : m_scenes) {
            scene->destroy_queued_components();
            scene->destroy_queued_entities();
        }
    }

} // namespace sly
