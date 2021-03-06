#include "BlueprintReflection/Type/Type.hpp"

namespace blueprint
{
namespace reflection
{
    void Type::SetTypeId(uint64_t typeId)
    {
        typeId_ = typeId;
    }

    uint64_t Type::GetTypeId() const
    {
        return typeId_;
    }

    void Type::SetSize(size_t size)
    {
        size_ = size;
    }

    size_t Type::GetSize() const
    {
        return size_;
    }

    void Type::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Type::GetName() const
    {
        return name_;
    }

    void Type::SetNamespace(const Namespace& ns)
    {
        namespace_ = ns;
    }

    const Namespace& Type::GetNamespace() const
    {
        return namespace_;
    }

    void Type::SetParentType(const TypeHandle& parentType)
    {
        parentType_ = parentType;
    }

    const TypeHandle& Type::GetParentType() const
    {
        return parentType_;
    }

    std::string Type::GetFullName() const
    {
        if (!name_.empty() && !namespace_.IsGlobal())
        {
            return namespace_.ToString() + "::" + name_;
        }

        return name_;
    }

    void Type::SetSourceLocation(const SourceLocation& location)
    {
        location_ = location;
    }

    const SourceLocation& Type::GetSourceLocation() const
    {
        return location_;
    }
}
}
