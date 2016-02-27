#include "Probe/Project.hpp"

namespace probe
{
    void Project::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Project::GetName() const
    {
        return name_;
    }

    void Project::SetDirectory(const std::string& directory)
    {
        directory_ = directory;
    }

    const std::string& Project::GetDirectory() const
    {
        return directory_;
    }

    void Project::AddConfiguration(std::unique_ptr<Configuration> configuration)
    {
        if (configuration.get() == nullptr)
        {
            return;
        }

        configurations_.push_back(std::move(configuration));
    }

    const Project::Configurations& Project::GetConfigurations()
    {
        return configurations_;
    }

    void Project::AddFile(const std::string& file)
    {
        files_.push_back(file);
    }

    const Project::StringArray& Project::GetFiles() const
    {
        return files_;
    }
}
