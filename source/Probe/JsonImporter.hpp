#pragma once

#include <Probe/Project.hpp>
#include <Probe/Workspace.hpp>

#include <memory>
#include <string>

namespace probe
{
    class JsonImporter
    {
    public:
        static std::unique_ptr<Workspace> ImportWorkspace(const std::string& filePath);
        static std::unique_ptr<Project> ImportProject(const std::string& filePath);
    };
}
