#pragma once

#include <filesystem/path.h>

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

    public:
        void SetListTypes(bool value) { listTypes_ = value; }
        void SetVerbose(bool value) { verbose_ = value; }

    public:
        bool ParseWorkspace(const filesystem::path& filePath);
        bool ParseWorkspace(const Workspace* workspace);

        bool ParseProject(const filesystem::path& filePath);
        bool ParseProject(const Project* project);

    private:
        bool ParseSourceFile(const filesystem::path& filePath, const Configuration* config);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;

        bool listTypes_{false};
        bool verbose_{false};
    };
}
