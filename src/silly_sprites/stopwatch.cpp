#include "stopwatch.hpp"

namespace sly {

    StopWatch::StopWatch() : m_start{ InternalClockType::now() } { }

    [[nodiscard]] double StopWatch::elapsed_time() const {
        return static_cast<double>(std::chrono::duration_cast<DurationType>(InternalClockType::now() - m_start).count())
               / tick_period_denominator;
    }

    void StopWatch::add_duration(double const start) {
        m_start -= DurationType(static_cast<RepresentationType>(start * tick_period_denominator));
    }

    double StopWatch::reset() {
        auto const result = elapsed_time();
        m_start = InternalClockType::now();
        return result;
    }

} // namespace sly
