#pragma once

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
}
