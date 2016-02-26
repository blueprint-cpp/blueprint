#include "Probe/Solution.hpp"

namespace probe
{
    void Solution::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Solution::GetName() const
    {
        return name_;
    }

    void Solution::AddProject(std::unique_ptr<Project> project)
    {
        if (project.get() == nullptr)
        {
            return;
        }

        projects_.push_back(std::move(project));
    }

    const Solution::Projects& Solution::GetProjects() const
    {
        return projects_;
    }
}
