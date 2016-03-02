#include "Blueprint/Reflection/TypeInfo.hpp"

namespace blueprint
{
namespace reflection
{
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
