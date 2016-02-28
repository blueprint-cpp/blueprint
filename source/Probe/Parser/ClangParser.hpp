#pragma once

#include <filesystem/path.h>

#include <memory>
#include <string>

#if defined(EXTERN_CLANG_ENABLED)

namespace probe
{
    class Configuration;
    class Project;
    class Workspace;

    class ClangParser
    {
    public:
        ClangParser();
        ~ClangParser();

        bool ParseWorkspace(const filesystem::path& filePath);
        bool ParseWorkspace(const Workspace* workspace);

        bool ParseProject(const filesystem::path& filePath);
        bool ParseProject(const Project* project);

    private:
        bool ParseSourceFile(const filesystem::path& filePath, const Configuration* config);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;
    };
}

#endif
