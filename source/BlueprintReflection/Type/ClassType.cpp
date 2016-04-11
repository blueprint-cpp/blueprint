#include "BlueprintReflection/Type/ClassType.hpp"

#include "BlueprintReflection/Visitor/TypeVisitor.hpp"

namespace blueprint
{
namespace reflection
{
    void ClassType::AddBaseClass(const ClassType* baseClass)
    {
        baseClasses_.push_back(baseClass);
    }

    const std::vector<const ClassType*>& ClassType::GetBaseClasses() const
    {
        return baseClasses_;
    }

    void ClassType::AddNestedType(const TypeHandle& nestedType)
    {
        if (nestedType.GetId() != 0)
        {
            nestedTypes_.push_back(nestedType);
        }
    }

    const std::vector<TypeHandle>& ClassType::GetNestedTypes() const
    {
        return nestedTypes_;
    }

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
