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
        using Projects = std::vector<std::unique_ptr<Project>>;

        void AddProject(std::unique_ptr<Project> project);
        const Projects& GetProjects() const;

    private:
        Projects projects_;

        std::string name_;
    };
}
