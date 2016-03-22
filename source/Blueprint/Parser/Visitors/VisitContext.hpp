#pragma once

#include "Blueprint/Reflection/Namespace.hpp"

#include <memory>

namespace blueprint { namespace clang { class Cursor; } }
namespace blueprint { namespace clang { class Type; } }
namespace blueprint { namespace reflection { class ClassType; } }
namespace blueprint { namespace reflection { class Type; } }
namespace blueprint { namespace reflection { class TypeRegistry; } }

namespace blueprint
{
namespace clang
{
    class VisitContext
    {
    public:
        VisitContext(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns);

        bool IsTypeRegistered(const clang::Type& type) const;
        const reflection::Type* FindType(const clang::Type& type) const;
        const reflection::ClassType* FindClass(const clang::Type& type) const;

        void RegisterType(std::unique_ptr<reflection::Type> type);
        void FillType(reflection::Type* type, const clang::Cursor& cursor, const clang::Cursor& parent);

    private:
        reflection::TypeRegistry& typeRegistry_;
        reflection::Namespace namespace_;
    };
}
}
