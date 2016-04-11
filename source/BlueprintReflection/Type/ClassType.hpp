#pragma once

#include "BlueprintReflection/Type/Field.hpp"
#include "BlueprintReflection/Type/Type.hpp"

namespace blueprint
{
namespace reflection
{
    class ClassType : public Type
    {
    public:
        void AddBaseClass(const ClassType* baseClass);
        const std::vector<const ClassType*>& GetBaseClasses() const;

        void AddNestedType(const TypeHandle& nestedType);
        const std::vector<TypeHandle>& GetNestedTypes() const;

        void AddMethod(const std::string& method);
        const std::vector<std::string>& GetMethods() const;

        void AddField(const Field& field);
        const std::vector<Field>& GetFields() const;

        virtual void Accept(TypeVisitor& visitor) const override;

    private:
        std::vector<const ClassType*> baseClasses_;
        std::vector<TypeHandle> nestedTypes_;

        std::vector<std::string> methods_;
        std::vector<Field> fields_;
    };
}
}
