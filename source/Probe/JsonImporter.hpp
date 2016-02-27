#pragma once

#include <Probe/Project.hpp>
#include <Probe/Workspace.hpp>

#include <filesystem/path.h>

#include <memory>
#include <string>

namespace probe
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(const filesystem::path& path);
        static std::unique_ptr<Project> ImportProject(const filesystem::path& path);
    };
}
