#pragma once

#include "Blueprint/Workspace/Workspace.hpp"

namespace blueprint { class FileSystem; }

namespace blueprint
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(FileSystem& fileSystem, const filesystem::path& workspaceFile);
        static std::unique_ptr<Project> ImportProject(FileSystem& fileSystem, const filesystem::path& projectFile);
    };
}
