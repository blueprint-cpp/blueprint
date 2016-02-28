#pragma once

#include "Probe/Workspace/Configuration.hpp"

#include <filesystem/path.h>
#include <memory>

namespace probe
{
    class Project
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

    public:
        using Configurations = std::vector<std::unique_ptr<Configuration>>;

        void AddConfiguration(std::unique_ptr<Configuration> configuration);
        const Configurations& GetConfigurations() const;

    public:
        using StringArray = std::vector<std::string>;

        void AddSource(const std::string& source);
        const StringArray& GetSources() const;

    private:
        std::string name_;
        filesystem::path file_;

        Configurations configurations_;
        StringArray sources_;
    };
}
