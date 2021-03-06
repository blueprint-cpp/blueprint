#include "Blueprint/Parser/Visitors/ClassVisitor.hpp"

#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"
#include "BlueprintClang/Cursor.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"

namespace blueprint
{
namespace clang
{
    void ClassVisitor::Visit(VisitContext& context, const clang::Cursor& cursor)
    {
        Visit(context, cursor, clang::Cursor());
    }

    void ClassVisitor::Visit(VisitContext& context, const clang::Cursor& cursor, const clang::Cursor& parent)
    {
        assert(cursor.IsOfKind(CXCursor_ClassDecl) || cursor.IsOfKind(CXCursor_StructDecl));

        if (cursor.IsDefinition() && !context.IsTypeRegistered(cursor.GetType()))
        {
            auto type = std::make_unique<reflection::ClassType>();
            context.FillType(type.get(), cursor, parent);

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

                case CXCursor_ClassDecl:
                case CXCursor_StructDecl:
                {
                    ClassVisitor::Visit(context, child, cursor);

                    classType->AddNestedType(child.GetType().GetTypeId());
                }
                break;

                case CXCursor_EnumDecl:
                {
                    EnumVisitor::Visit(context, child, cursor);

                    classType->AddNestedType(child.GetType().GetTypeId());
                }
                break;

                default:
                    break;
            }
        }
    }
}
}
