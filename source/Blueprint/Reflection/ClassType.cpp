#include "Blueprint/Reflection/ClassType.hpp"

#include "Blueprint/Reflection/Visitors/TypeVisitor.hpp"

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

    void ClassType::AddField(const Field& field)
    {
        fields_.push_back(field);
    }

    const std::vector<Field>& ClassType::GetFields() const
    {
        return fields_;
    }

    void ClassType::Accept(TypeVisitor& visitor) const
    {
        visitor.Visit(*this);
    }
}
}
