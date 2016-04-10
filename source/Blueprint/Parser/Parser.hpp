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
        inline void SetListTypes(bool value) { listTypes_ = value; }
        inline void SetVerbose(bool value) { verbose_ = value; }
        inline void SetOutputDirectory(const filesystem::path& outputDirectory) { outputDirectory_ = outputDirectory; }

    public:
        bool ParseWorkspace(const filesystem::path& filePath);
        bool ParseWorkspace(const Workspace* workspace);

        bool ParseProject(const filesystem::path& filePath);
        bool ParseProject(const Project* project);

    private:
        struct FileContext;
        bool ParseSourceFile(FileContext& context);

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;

        filesystem::path outputDirectory_;

        bool listTypes_{false};
        bool verbose_{false};
    };
}
