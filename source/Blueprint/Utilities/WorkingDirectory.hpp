#pragma once

#include <string>

namespace blueprint
{
    class WorkingDirectory
    {
    public:
        static void SetCurrent(const std::string& directory);
        static std::string GetCurrent();
    };
}
