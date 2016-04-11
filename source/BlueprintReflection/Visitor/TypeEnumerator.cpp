#include "BlueprintReflection/Visitor/TypeEnumerator.hpp"

#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"

namespace blueprint
{
namespace reflection
{
    void TypeEnumerator::Visit(const ClassType& type)
    {
        classes_.push_back(&type);
    }

    void TypeEnumerator::Visit(const EnumType& type)
    {
        enums_.push_back(&type);
    }

    const std::vector<const ClassType*>& TypeEnumerator::GetClasses() const
    {
        return classes_;
    }

    const std::vector<const EnumType*>& TypeEnumerator::GetEnums() const
    {
        return enums_;
    }
}
}
