#pragma once

#include "Blueprint/Reflection/Type.hpp"

namespace blueprint
{
namespace reflection
{
    class ClassType : public Type
    {
    public:
        void AddMethod(const std::string& method);
        const std::vector<std::string>& GetMethods() const;

        void AddField(const std::string& field);
        const std::vector<std::string>& GetFields() const;

    private:
        std::vector<std::string> methods_;
        std::vector<std::string> fields_;
    };
}
}
