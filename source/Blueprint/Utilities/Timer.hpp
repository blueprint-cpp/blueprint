#pragma once

#include <chrono>
#include <functional>

namespace blueprint
{
    class Timer
    {
    public:
        void Start()
        {
            start_ = std::chrono::system_clock::now();
        }

        void Stop()
        {
            end_ = std::chrono::system_clock::now();
        }

        double GetDuration() const
        {
            std::chrono::duration<double> duration = end_ - start_;
            return duration.count();
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> start_;
        std::chrono::time_point<std::chrono::system_clock> end_;
    };

    class ScopeTimer
    {
        using ReportFunctor = std::function<void(double)>;

    public:
        ScopeTimer(const ReportFunctor& report)
            : report_(report)
        {
            timer_.Start();
        }

        ~ScopeTimer()
        {
            timer_.Stop();

            report_(timer_.GetDuration());
        }

    private:
        ReportFunctor report_;
        Timer timer_;
    };
}
