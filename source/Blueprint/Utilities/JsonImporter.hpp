#pragma once

#include "Blueprint/Workspace/Workspace.hpp"

namespace blueprint
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(const filesystem::path& workspaceFile);
        static std::unique_ptr<Project> ImportProject(const filesystem::path& projectFile);
    };
}
