#pragma once

#include <string>

namespace blueprint
{
    class TypeInfo
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetNamespace(const std::string& nameSpace);
        const std::string& GetNamespace() const;

        std::string GetFullName() const;

    private:
        std::string name_;
        std::string namespace_;
    };
}
