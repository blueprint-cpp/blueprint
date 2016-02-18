#pragma once

#include "Probe/Project.hpp"

#include <memory>
#include <string>
#include <vector>

namespace probe
{
    class Solution
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

    public:
        using ProjectCollection = std::vector<std::unique_ptr<Project>>;

        const ProjectCollection& GetProjects() const;
        void AddProject(std::unique_ptr<Project> project);

    private:
        ProjectCollection projects_;

        std::string name_;
    };
}
