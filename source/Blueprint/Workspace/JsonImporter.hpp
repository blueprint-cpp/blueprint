#pragma once

#include <Blueprint/Workspace/Workspace.hpp>

namespace blueprint
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(const filesystem::path& path);
        static std::unique_ptr<Project> ImportProject(const filesystem::path& path);
    };
}
