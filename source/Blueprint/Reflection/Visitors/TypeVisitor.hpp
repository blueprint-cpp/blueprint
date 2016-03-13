#pragma once

namespace blueprint
{
namespace reflection
{
    class ClassType;
    class EnumType;

    class TypeVisitor
    {
    public:
        virtual void Visit(const ClassType& type) = 0;
        virtual void Visit(const EnumType&  type) = 0;
    };
}
}
