#pragma once

#include "stopwatch.hpp"
#include "time.hpp"
#include <memory>
#include <variant>
#include <vector>

namespace sly {

    class Scene;

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
        std::vector<std::unique_ptr<Scene>> m_scenes;

    public:
        explicit Application(ApplicationSettings settings);

        virtual ~Application();

        void run();

    private:
        static constexpr auto s_fixed_update_interval = 1.0 / 60.0;

        void fixed_update(Time time);
        void update(Time time);
        void render() const;
        void process_queued_scene_tasks();
    };

} // namespace sly
