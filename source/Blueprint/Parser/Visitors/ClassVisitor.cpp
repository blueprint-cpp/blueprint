#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Reflection/ClassType.hpp"

#include <cassert>

namespace blueprint
{
    void ClassVisitor::Visit(VisitContext& context, const clang::Cursor& cursor)
    {
        assert(cursor.IsOfKind(CXCursor_ClassDecl) || cursor.IsOfKind(CXCursor_StructDecl));

        if (!context.IsTypeRegistered(cursor.GetType()))
        {
            auto type = std::make_unique<reflection::ClassType>();
            context.FillType(type.get(), cursor);

            FillClass(type.get(), cursor);
            context.RegisterType(std::move(type));
        }
    }

    void ClassVisitor::FillClass(reflection::ClassType* classType, const clang::Cursor& cursor)
    {
        assert(classType != nullptr);

        for (auto& child : cursor.GetChildren())
        {
            switch (child.GetKind())
            {
                case CXCursor_CXXMethod:
                {
                    // TODO
                }
                break;

                case CXCursor_FieldDecl:
                {
                    // TODO
                }
                break;

                default:
                    break;
            }
        }
    }
}

#endif
