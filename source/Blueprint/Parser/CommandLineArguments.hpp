#pragma once

#include <filesystem/path.h>

namespace blueprint
{
    class Configuration;

    class CommandLineArguments
    {
    public:
        void Add(const std::string& argument);
        const std::vector<std::string>& GetArguments();

        void ImportConfig(const Configuration* config, const filesystem::path& path);

    private:
        std::vector<std::string> arguments_;
    };
}
