#pragma once

#include <string>
#include <vector>

namespace blueprint
{
    class Configuration;

    class CommandLineArguments
    {
    public:
        void Add(const std::string& argument);
        const std::vector<std::string>& GetArguments();

        void ImportConfig(const Configuration* config);

    private:
        std::vector<std::string> arguments_;
    };
}
