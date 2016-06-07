#pragma once

#include "Blueprint/Workspace/Workspace.hpp"

namespace blueprint { class FileManager; }

namespace blueprint
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(FileManager& fileManager, const filesystem::path& workspaceFile);
        static std::unique_ptr<Project> ImportProject(FileManager& fileManager, const filesystem::path& projectFile);
    };
}
