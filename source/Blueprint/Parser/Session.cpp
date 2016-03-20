#include "Blueprint/Parser/Session.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
    void Session::SetWorkspace(const filesystem::path& workspace)
    {
        workspace_ = workspace;
    }

    const filesystem::path& Session::GetWorkspace() const
    {
        return workspace_;
    }

    void Session::SetOutputDirectory(const filesystem::path& outputDirectory)
    {
        outputDirectory_ = outputDirectory;
    }

    const filesystem::path& Session::GetOutputDirectory() const
    {
        return outputDirectory_;
    }

    void Session::AddArgument(const std::string& argument)
    {
        arguments_.push_back(argument);
    }

    const std::vector<std::string>& Session::GetArguments() const
    {
        return arguments_;
    }
}

#endif
