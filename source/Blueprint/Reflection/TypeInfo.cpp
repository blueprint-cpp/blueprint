#include "Blueprint/Reflection/TypeInfo.hpp"

namespace blueprint
{
    void TypeInfo::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& TypeInfo::GetName() const
    {
        return name_;
    }

    void TypeInfo::SetNamespace(const std::string& nameSpace)
    {
        namespace_ = nameSpace;
    }

    const std::string& TypeInfo::GetNamespace() const
    {
        return namespace_;
    }

    std::string TypeInfo::GetFullName() const
    {
        if (!name_.empty())
        {
            return !namespace_.empty() ? namespace_ + "::" + name_ : name_;
        }

        return "";
    }
}
