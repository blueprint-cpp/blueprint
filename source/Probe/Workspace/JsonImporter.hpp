#pragma once

#include <Probe/Workspace/Workspace.hpp>

namespace probe
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(const filesystem::path& path);
        static std::unique_ptr<Project> ImportProject(const filesystem::path& path);
    };
}
