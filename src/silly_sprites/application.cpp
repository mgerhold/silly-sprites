#include "application.hpp"
#include <spdlog/spdlog.h>

namespace sly {

    void Application::run() {
        auto is_running = true;
        m_stopwatch.reset();

        auto last_fixed_update = m_stopwatch.elapsed_time();
        auto last_update = m_stopwatch.elapsed_time();

        while (is_running) {
            auto elapsed_since_last_fixed_update = m_stopwatch.elapsed_time() - last_fixed_update;
            while (elapsed_since_last_fixed_update >= s_fixed_update_interval) {
                fixed_update();
                last_fixed_update += s_fixed_update_interval;
                elapsed_since_last_fixed_update = m_stopwatch.elapsed_time() - last_fixed_update;
            }

            if (std::holds_alternative<refresh_rate::Unlimited>(m_settings.refresh_rate)
                or std::holds_alternative<refresh_rate::VSync>(m_settings.refresh_rate)) {
                auto const delta_time = m_stopwatch.elapsed_time() - last_update;
                last_update = m_stopwatch.elapsed_time();
                update(delta_time);
                render();
            } else if (std::holds_alternative<refresh_rate::Limited>(m_settings.refresh_rate)) {
                auto const refresh_rate = std::get<refresh_rate::Limited>(m_settings.refresh_rate).limit;
                auto const elapsed_since_last_update = m_stopwatch.elapsed_time() - last_update;
                if (elapsed_since_last_update >= 1.0 / refresh_rate) {
                    last_update = m_stopwatch.elapsed_time();
                    update(elapsed_since_last_update);
                    render();
                }
            }
        }
    }

    void Application::fixed_update() {
        for (auto& scene : m_scenes) {
            scene.fixed_update();
        }
    }

    void Application::update(double const delta_time) {
        for (auto& scene : m_scenes) {
            scene.update(delta_time);
        }
    }

    void Application::render() const {
        spdlog::info("render()");
    }

} // namespace sly
