#include "Blueprint/Workspace/Project.hpp"

namespace blueprint
{
    void Project::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Project::GetName() const
    {
        return name_;
    }

    void Project::SetFile(const filesystem::path& file)
    {
        file_ = file;
    }

    const filesystem::path& Project::GetFile() const
    {
        return file_;
    }

    void Project::AddConfiguration(std::unique_ptr<Configuration> configuration)
    {
        if (configuration.get() == nullptr)
        {
            return;
        }

        configurations_.push_back(std::move(configuration));
    }

    const Project::Configurations& Project::GetConfigurations() const
    {
        return configurations_;
    }

    void Project::AddFile(std::shared_ptr<File> file)
    {
        files_.push_back(file);
    }

    const Project::Files& Project::GetFiles() const
    {
        return files_;
    }
}
