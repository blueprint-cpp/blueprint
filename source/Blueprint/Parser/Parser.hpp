#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include <filesystem/path.h>

#include <memory>
#include <string>

namespace blueprint
{
    class Configuration;
    class Project;
    class Workspace;

    class Parser
    {
    public:
        Parser();
        ~Parser();

        bool ParseWorkspace(const filesystem::path& filePath);
        bool ParseWorkspace(const Workspace* workspace);

        bool ParseProject(const filesystem::path& filePath);
        bool ParseProject(const Project* project);

    private:
        bool ParseSourceFile(const filesystem::path& filePath, const Configuration* config);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;

        bool verbose_{false};
    };
}

#endif
