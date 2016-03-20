#include "Blueprint/Parser/ParsingSession.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
    void ParsingSession::SetWorkspace(const filesystem::path& workspace)
    {
        workspace_ = workspace;
    }

    const filesystem::path& ParsingSession::GetWorkspace() const
    {
        return workspace_;
    }

    void ParsingSession::SetOutputDirectory(const filesystem::path& outputDirectory)
    {
        outputDirectory_ = outputDirectory;
    }

    const filesystem::path& ParsingSession::GetOutputDirectory() const
    {
        return outputDirectory_;
    }

    void ParsingSession::AddArgument(const std::string& argument)
    {
        arguments_.push_back(argument);
    }

    const std::vector<std::string>& ParsingSession::GetArguments() const
    {
        return arguments_;
    }
}

#endif
