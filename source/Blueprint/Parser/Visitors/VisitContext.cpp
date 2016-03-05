#include "Blueprint/Parser/Visitors/VisitContext.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Reflection/Namespace.hpp"
#include "Blueprint/Reflection/Type.hpp"
#include "Blueprint/Reflection/TypeRegistry.hpp"

#include <cassert>

namespace blueprint
{
    VisitContext::VisitContext(reflection::TypeRegistry& typeRegistry, const reflection::Namespace& ns)
        : typeRegistry_(typeRegistry)
        , namespace_(ns)
    {}

    bool VisitContext::IsTypeRegistered(uint64_t typeId) const
    {
        return typeRegistry_.Contains(typeId);
    }

    void VisitContext::RegisterType(std::unique_ptr<reflection::Type> type)
    {
        typeRegistry_.Register(std::move(type));
    }

    void VisitContext::FillType(reflection::Type* type, const clang::Cursor& cursor)
    {
        assert(type != nullptr);

        std::hash<std::string> hash;

        type->SetName(cursor.GetSpelling());
        type->SetNamespace(namespace_);
        type->SetTypeId(hash(type->GetFullName()));

        auto cursorLocation = cursor.GetSourceLocation();

        reflection::SourceLocation typeLocation;

        typeLocation.SetFile(cursorLocation.GetFile());
        typeLocation.SetLine(cursorLocation.GetLine());
        typeLocation.SetColumn(cursorLocation.GetColumn());

        type->SetSourceLocation(typeLocation);
    }
}

#endif
