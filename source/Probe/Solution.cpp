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

    const Solution::ProjectCollection& Solution::GetProjects() const
    {
        return projects_;
     }

    void Solution::AddProject(std::unique_ptr<Project> project)
    {
        projects_.push_back(std::move(project));
    }
}
