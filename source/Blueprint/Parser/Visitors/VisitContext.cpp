#include "Blueprint/Parser/Visitors/VisitContext.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Reflection/ClassType.hpp"
#include "Blueprint/Reflection/Namespace.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

#include <cassert>

namespace blueprint
{
    VisitContext::VisitContext(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns)
        : typeRegistry_(typeRegistry)
        , namespace_(ns)
    {}

    bool VisitContext::IsTypeRegistered(const clang::Type& type) const
    {
        return typeRegistry_.Contains(type.GetTypeId());
    }

    const reflection::Type* VisitContext::FindType(const clang::Type& type) const
    {
        return typeRegistry_.Find(type.GetTypeId());
    }

    const reflection::ClassType* VisitContext::FindClass(const clang::Type& type) const
    {
        return dynamic_cast<const reflection::ClassType*>(FindType(type));
    }

    void VisitContext::RegisterType(std::unique_ptr<reflection::Type> type)
    {
        typeRegistry_.Register(std::move(type));
    }

    void VisitContext::FillType(reflection::Type* type, const clang::Cursor& cursor, const clang::Cursor& parent)
    {
        assert(type != nullptr);

        auto cursorType = cursor.GetType();

        type->SetTypeId(cursorType.GetTypeId());
        type->SetSize(cursorType.GetSizeOf());
        type->SetName(cursor.GetSpelling().Get());
        type->SetNamespace(namespace_);

        if (!parent.IsNull())
        {
            type->SetParentType(parent.GetType().GetTypeId());
        }

        auto cursorLocation = cursor.GetSourceLocation();

        reflection::SourceLocation typeLocation;

        typeLocation.SetFile(cursorLocation.GetFile());
        typeLocation.SetLine(cursorLocation.GetLine());
        typeLocation.SetColumn(cursorLocation.GetColumn());

        type->SetSourceLocation(typeLocation);
    }
}

#endif
