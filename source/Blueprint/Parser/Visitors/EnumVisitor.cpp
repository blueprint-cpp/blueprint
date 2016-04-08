#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Reflection/EnumType.hpp"

namespace blueprint
{
namespace clang
{
    void EnumVisitor::Visit(VisitContext& context, const clang::Cursor& cursor)
    {
        Visit(context, cursor, clang::Cursor());
    }

    void EnumVisitor::Visit(VisitContext& context, const clang::Cursor& cursor, const clang::Cursor& parent)
    {
        assert(cursor.IsOfKind(CXCursor_EnumDecl));

        if (cursor.IsDefinition() && !context.IsTypeRegistered(cursor.GetType()))
        {
            auto type = std::make_unique<reflection::EnumType>();
            context.FillType(type.get(), cursor, parent);

            FillEnum(type.get(), cursor);
            context.RegisterType(std::move(type));
        }
    }

    void EnumVisitor::FillEnum(reflection::EnumType* enumType, const clang::Cursor& cursor)
    {
        assert(enumType != nullptr);

        for (auto& child : cursor.GetChildren())
        {
            assert(child.IsOfKind(CXCursor_EnumConstantDecl));

            auto value = clang_getEnumConstantDeclValue(CXCursor(child));

            enumType->AddEntry(child.GetSpelling().Get(), value);
        }
    }
}
}
