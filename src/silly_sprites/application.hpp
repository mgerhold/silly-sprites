#pragma once

#include "scene.hpp"
#include "stopwatch.hpp"
#include <variant>
#include <vector>

namespace sly {

    namespace refresh_rate {
        struct Unlimited { };
        struct VSync { };
        struct Limited {
            double limit;
        };
    } // namespace refresh_rate

    using RefreshRate = std::variant<refresh_rate::Unlimited, refresh_rate::VSync, refresh_rate::Limited>;

    struct ApplicationSettings {
        RefreshRate refresh_rate;

        ApplicationSettings() : refresh_rate{ refresh_rate::Unlimited{} } { }
    };

    class Application {
    private:
        ApplicationSettings m_settings;
        StopWatch m_stopwatch;
        std::vector<Scene> m_scenes;

    public:
        explicit Application(ApplicationSettings settings) : m_settings{ settings } {
            m_scenes.emplace_back();
        }

        virtual ~Application() = default;

        void run();

    private:
        static constexpr auto s_fixed_update_interval = 1.0 / 60.0;

        void fixed_update();
        void update(double delta_time);
        void render() const;
    };

} // namespace sly
