#pragma once

namespace blueprint
{
    class Configuration;

    class CommandLineArguments
    {
    public:
        void Add(const std::string& argument);
        const std::vector<std::string>& GetArguments() const;

        void ImportConfig(const Configuration* config);

    private:
        std::vector<std::string> arguments_;
    };
}
