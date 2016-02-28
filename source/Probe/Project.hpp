#pragma once

#include "Probe/Configuration.hpp"

#include <memory>
#include <string>
#include <vector>

namespace probe
{
    class Project
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetDirectory(const std::string& directory);
        const std::string& GetDirectory() const;

    public:
        using Configurations = std::vector<std::unique_ptr<Configuration>>;

        void AddConfiguration(std::unique_ptr<Configuration> configuration);
        const Configurations& GetConfigurations() const;

    public:
        using StringArray = std::vector<std::string>;

        void AddFile(const std::string& file);
        const StringArray& GetFiles() const;

    private:
        std::string name_;
        std::string directory_;

        Configurations configurations_;
        StringArray files_;
    };
}
