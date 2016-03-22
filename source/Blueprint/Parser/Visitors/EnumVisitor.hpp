#pragma once

#include "Blueprint/Parser/Visitors/VisitContext.hpp"

namespace blueprint { namespace reflection { class EnumType; } }

namespace blueprint
{
namespace clang
{
    class EnumVisitor
    {
    public:
        static void Visit(VisitContext& context, const clang::Cursor& cursor);
        static void Visit(VisitContext& context, const clang::Cursor& cursor, const clang::Cursor& parent);

    private:
        static void FillEnum(reflection::EnumType* enumType, const clang::Cursor& cursor);
    };
}
}
