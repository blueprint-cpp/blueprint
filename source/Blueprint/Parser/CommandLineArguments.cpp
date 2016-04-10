#include "Blueprint/Parser/CommandLineArguments.hpp"

#include "Blueprint/Workspace/Configuration.hpp"

namespace blueprint
{
    void CommandLineArguments::Add(const std::string& argument)
    {
        arguments_.push_back(argument);
    }

    const std::vector<std::string>& CommandLineArguments::GetArguments() const
    {
        return arguments_;
    }

    void CommandLineArguments::ImportConfig(const Configuration* config)
    {
        if (config == nullptr)
        {
            return;
        }

        for (auto& define : config->GetDefines())
        {
            Add("-D" + define);
        }

        for (auto& include : config->GetIncludes())
        {
            Add("-I" + include);
        }
    }

    void CommandLineArguments::Save(const filesystem::path& filePath) const
    {
        std::ofstream stream(filePath.str());

        if (stream.is_open())
        {
            for (auto& arg : arguments_)
            {
                stream << arg << std::endl;;
            }

            stream.close();
        }
    }
}
