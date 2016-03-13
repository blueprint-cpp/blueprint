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

            FillClass(context, type.get(), cursor);
            context.RegisterType(std::move(type));
        }
    }

    void ClassVisitor::FillClass(VisitContext& context, reflection::ClassType* classType, const clang::Cursor& cursor)
    {
        assert(classType != nullptr);

        for (auto& child : cursor.GetChildren())
        {
            switch (child.GetKind())
            {
                case CXCursor_CXXBaseSpecifier:
                {
                    classType->AddBaseClass(context.FindClass(child.GetType()));
                }
                break;

                case CXCursor_CXXMethod:
                {
                    classType->AddMethod(child.GetSpelling().Get());
                }
                break;

                case CXCursor_FieldDecl:
                {
                    auto fieldName = child.GetSpelling().Get();
                    auto fieldType = child.GetType();

                    reflection::Field field;
                    field.SetName(fieldName);
                    field.SetSize(fieldType.GetSizeOf());
                    field.SetOffset(child.GetOffsetOfField());

                    classType->AddField(field);
                }
                break;

                default:
                    break;
            }
        }
    }
}

#endif
