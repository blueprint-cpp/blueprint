#pragma once

#include "Blueprint/Reflection/Visitors/TypeVisitor.hpp"

#include <vector>

namespace blueprint
{
namespace reflection
{
    class TypeEnumerator : public TypeVisitor
    {
    public:
        virtual void Visit(const TypeRegistry& /*registry*/) override {}
        virtual void Visit(const ClassType& type) override;
        virtual void Visit(const EnumType& type) override;

    public:
        const std::vector<const ClassType*>& GetClasses() const;
        const std::vector<const EnumType*>& GetEnums() const;

    private:
        std::vector<const ClassType*> classes_;
        std::vector<const EnumType*> enums_;
    };
}
}
