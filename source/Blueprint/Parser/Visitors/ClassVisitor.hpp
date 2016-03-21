#pragma once

#include "Blueprint/Parser/Visitors/VisitContext.hpp"

namespace blueprint { namespace reflection { class ClassType; } }

namespace blueprint
{
    class ClassVisitor
    {
    public:
        static void Visit(VisitContext& context, const clang::Cursor& cursor);
        static void Visit(VisitContext& context, const clang::Cursor& cursor, const clang::Cursor& parent);

    private:
        static void FillClass(VisitContext& context, reflection::ClassType* classType, const clang::Cursor& cursor);
    };
}
