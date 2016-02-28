#pragma once

#include "Blueprint/Workspace/Project.hpp"

#include <filesystem/path.h>
#include <memory>

namespace blueprint
{
    class Workspace
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

    public:
        using Projects = std::vector<std::unique_ptr<Project>>;

        void AddProject(std::unique_ptr<Project> project);
        const Projects& GetProjects() const;

    private:
        Projects projects_;

        std::string name_;
        filesystem::path file_;
    };
}
