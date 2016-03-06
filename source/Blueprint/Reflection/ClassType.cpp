#include "Blueprint/Reflection/ClassType.hpp"

namespace blueprint
{
namespace reflection
{
    void ClassType::AddMethod(const std::string& method)
    {
        methods_.push_back(method);
    }

    const std::vector<std::string>& ClassType::GetMethods() const
    {
        return methods_;
    }

    void ClassType::AddField(const std::string& field)
    {
        fields_.push_back(field);
    }

    const std::vector<std::string>& ClassType::GetFields() const
    {
        return fields_;
    }
}
}
