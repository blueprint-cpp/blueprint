#pragma once

#include <string>
#include <vector>

namespace probe
{
    class Project
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

    public:
        using StringArray = std::vector<std::string>;

        void AddFile(const std::string& file);
        const StringArray& GetFiles() const;

    private:
        std::string name_;

        StringArray files_;
    };
}
