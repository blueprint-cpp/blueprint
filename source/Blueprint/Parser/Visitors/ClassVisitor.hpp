#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Visitors/VisitContext.hpp"

namespace blueprint { namespace reflection { class ClassType; } }

namespace blueprint
{
    class ClassVisitor
    {
    public:
        static void Visit(VisitContext& context, const clang::Cursor& cursor);

    private:
        static void FillClass(VisitContext& context, reflection::ClassType* classType, const clang::Cursor& cursor);
    };
}

#endif
