#pragma once

namespace blueprint
{
namespace reflection
{
    class ClassType;
    class EnumType;
    class TypeRegistry;

    class TypeVisitor
    {
    public:
        virtual ~TypeVisitor() = default;

        virtual void Visit(const TypeRegistry& registry) = 0;
        virtual void Visit(const ClassType& type) = 0;
        virtual void Visit(const EnumType& type) = 0;
    };
}
}
