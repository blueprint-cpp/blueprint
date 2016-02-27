#include "Probe/Workspace.hpp"

namespace probe
{
    void Workspace::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Workspace::GetName() const
    {
        return name_;
    }

    void Workspace::AddProject(std::unique_ptr<Project> project)
    {
        if (project.get() == nullptr)
        {
            return;
        }

        projects_.push_back(std::move(project));
    }

    const Workspace::Projects& Workspace::GetProjects() const
    {
        return projects_;
    }
}
