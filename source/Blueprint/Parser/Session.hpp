#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include <filesystem/path.h>

namespace blueprint
{
    class Session
    {
    public:
        void SetWorkspace(const filesystem::path& workspace);
        const filesystem::path& GetWorkspace() const;

        void SetOutputDirectory(const filesystem::path& outputDirectory);
        const filesystem::path& GetOutputDirectory() const;

        void AddArgument(const std::string& argument);
        const std::vector<std::string>& GetArguments() const;

    private:
        std::vector<std::string> arguments_;

        filesystem::path workspace_;
        filesystem::path outputDirectory_;
    };
}

#endif
