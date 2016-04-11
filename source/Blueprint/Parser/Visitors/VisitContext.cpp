#include "Blueprint/Parser/Visitors/VisitContext.hpp"

#include "BlueprintClang/Cursor.hpp"
#include "BlueprintReflection/Registry/TypeRegistry.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/Namespace.hpp"

namespace blueprint
{
namespace clang
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

        auto cursorRange = cursor.GetSourceRange();
        auto cursorStart = cursorRange.GetStart();
        auto cursorEnd = cursorRange.GetEnd();

        reflection::SourceLocation location;

        location.SetFile(cursorRange.GetStart().GetFile());

        location.GetStartPosition().SetLine(cursorStart.GetLine());
        location.GetStartPosition().SetColumn(cursorStart.GetColumn());
        location.GetStartPosition().SetOffset(cursorStart.GetOffset());

        location.GetEndPosition().SetLine(cursorEnd.GetLine());
        location.GetEndPosition().SetColumn(cursorEnd.GetColumn());
        location.GetEndPosition().SetOffset(cursorEnd.GetOffset());

        type->SetSourceLocation(location);
    }
}
}
