#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Reflection/Namespace.hpp"

#include <memory>

namespace blueprint { namespace clang { class Cursor; } }
namespace blueprint { namespace reflection { class Type; } }
namespace blueprint { namespace reflection { class TypeRegistry; } }

namespace blueprint
{
    class VisitContext
    {
    public:
        VisitContext(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns);

        bool IsTypeRegistered(uint64_t typeId) const;
        void RegisterType(std::unique_ptr<reflection::Type> type);

        void FillType(reflection::Type* type, const clang::Cursor& cursor);

    private:
        reflection::TypeRegistry& typeRegistry_;
        reflection::Namespace namespace_;
    };
}

#endif
