#include "Blueprint/Parser/Visitors/EnumVisitor.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Reflection/EnumType.hpp"

#include <cassert>

namespace blueprint
{
    void EnumVisitor::Visit(VisitContext& context, const clang::Cursor& cursor)
    {
        assert(cursor.IsOfKind(CXCursor_EnumDecl));

        auto type = std::make_unique<reflection::EnumType>();
        context.FillType(type.get(), cursor);

        if (!context.IsTypeRegistered(type->GetTypeId()))
        {
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

#endif
