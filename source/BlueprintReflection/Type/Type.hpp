#pragma once

#include "BlueprintReflection/Type/Namespace.hpp"
#include "BlueprintReflection/Type/SourceLocation.hpp"
#include "BlueprintReflection/Type/TypeHandle.hpp"

namespace blueprint
{
namespace reflection
{
    class TypeVisitor;

    class Type
    {
    public:
        virtual ~Type() = default;

        void SetTypeId(uint64_t typeId);
        uint64_t GetTypeId() const;

        void SetSize(size_t size);
        size_t GetSize() const;

        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetNamespace(const Namespace& ns);
        const Namespace& GetNamespace() const;

        void SetParentType(const TypeHandle& parentType);
        const TypeHandle& GetParentType() const;

        std::string GetFullName() const;

        void SetSourceLocation(const SourceLocation& location);
        const SourceLocation& GetSourceLocation() const;

    public:
        virtual void Accept(TypeVisitor& visitor) const = 0;

    private:
        uint64_t typeId_{0};
        size_t size_{0};

        std::string name_;
        Namespace namespace_;

        TypeHandle parentType_;

        SourceLocation location_;
    };
}
}
