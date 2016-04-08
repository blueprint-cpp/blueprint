#pragma once

#include "Blueprint/Utilities/Timer.hpp"

namespace blueprint
{
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
