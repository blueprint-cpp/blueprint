#include "Probe/Parser/CommandLineArguments.hpp"

#include "Probe/Workspace/Configuration.hpp"

namespace probe
{
    void CommandLineArguments::Add(const std::string& argument)
    {
        arguments_.push_back(argument);
    }

    void CommandLineArguments::ImportConfig(const Configuration* config, const filesystem::path& path)
    {
        if (config)
        {
            for (auto& define : config->GetDefines())
            {
                Add("-D" + define);
            }

            if (path.str().empty())
            {
                for (auto& include : config->GetIncludes())
                {
                    Add("-I" + include);
                }
            }
            else
            {
                for (auto& include : config->GetIncludes())
                {
                    Add("-I" + (path / include).str());
                }
            }
        }
    }

    const std::vector<std::string>& CommandLineArguments::GetArguments()
    {
        return arguments_;
    }
}
