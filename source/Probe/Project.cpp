#include "Probe/Project.hpp"

namespace probe
{
    void Project::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Project::GetName() const
    {
        return name_;
    }
}
