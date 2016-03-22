#pragma once

#include "Blueprint/Reflection/Namespace.hpp"

namespace blueprint { namespace clang { class Cursor; } }
namespace blueprint { namespace reflection { class TypeRegistry; } }

namespace blueprint
{
namespace clang
{
    class NamespaceVisitor
    {
    public:
        NamespaceVisitor(reflection::TypeRegistry& typeRegistry);
        NamespaceVisitor(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns);

        void Visit(const clang::Cursor& cursor);

    private:
        reflection::TypeRegistry& typeRegistry_;
        reflection::Namespace namespace_;
    };
}
}
