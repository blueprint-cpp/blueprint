#pragma once

#include <string>

namespace probe
{
    class Project
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

    private:
        std::string name_;
    };
}
