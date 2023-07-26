#pragma once


#include <chrono>

namespace sly {

    class StopWatch final {
    public:
        StopWatch();
        [[nodiscard]] double elapsed_time() const;
        void add_duration(double start);
        double reset();

    private:
        using InternalClockType = std::chrono::steady_clock;

        using DurationType = std::chrono::nanoseconds;
        using RepresentationType = DurationType::rep;
        static constexpr intmax_t tick_period_denominator = DurationType::period::den;

        std::chrono::time_point<InternalClockType> m_start;
    };

} // namespace sly
