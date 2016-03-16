#pragma once

#include "Blueprint/Reflection/Field.hpp"
#include "Blueprint/Reflection/Type.hpp"

namespace blueprint
{
namespace reflection
{
    class ClassType : public Type
    {
    public:
        void AddBaseClass(const ClassType* baseClass);
        const std::vector<const ClassType*>& GetBaseClasses() const;

        void AddNestedType(const Type* nestedType);
        const std::vector<const Type*>& GetNestedTypes() const;

        void AddMethod(const std::string& method);
        const std::vector<std::string>& GetMethods() const;

        void AddField(const Field& field);
        const std::vector<Field>& GetFields() const;

        virtual void Accept(TypeVisitor& visitor) const override;

    private:
        std::vector<const ClassType*> baseClasses_;
        std::vector<const Type*> nestedTypes_;

        std::vector<std::string> methods_;
        std::vector<Field> fields_;
    };
}
}
