#include "Blueprint/Reflection/Visitors/TypeEnumerator.hpp"

#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/EnumType.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

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
