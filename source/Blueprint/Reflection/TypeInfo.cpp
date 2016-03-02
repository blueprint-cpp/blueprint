#include "Blueprint/Reflection/TypeInfo.hpp"

namespace blueprint
{
namespace reflection
{
    void TypeInfo::SetTypeId(uint64_t typeId)
    {
        typeId_ = typeId;
    }

    uint64_t TypeInfo::GetTypeId() const
    {
        return typeId_;
    }

    void TypeInfo::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& TypeInfo::GetName() const
    {
        return name_;
    }

    void TypeInfo::SetNamespace(const Namespace& ns)
    {
        namespace_ = ns;
    }

    const Namespace& TypeInfo::GetNamespace() const
    {
        return namespace_;
    }

    std::string TypeInfo::GetFullName() const
    {
        if (!name_.empty() && !namespace_.IsGlobal())
        {
            return namespace_.ToString() + "::" + name_;
        }

        return name_;
    }
}
}
