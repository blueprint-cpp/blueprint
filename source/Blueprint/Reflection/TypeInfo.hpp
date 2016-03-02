#pragma once

#include "Blueprint/Reflection/Namespace.hpp"

namespace blueprint
{
namespace reflection
{
    class TypeInfo
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetNamespace(const Namespace& ns);
        const Namespace& GetNamespace() const;

        std::string GetFullName() const;

    private:
        //uint64_t typeID_{0};
        std::string name_;
        Namespace namespace_;
    };
}
}
