#include "Blueprint/Parser/Clang/Cursor.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/String.hpp"

namespace blueprint
{
namespace clang
{
    bool Cursor::IsInSystemHeader() const
    {
        auto location = clang_getCursorLocation(cursor_);
        return clang_Location_isInSystemHeader(location) != 0;
    }

    bool Cursor::IsFromMainFile() const
    {
        auto location = clang_getCursorLocation(cursor_);
        return clang_Location_isFromMainFile(location) != 0;
    }

    bool Cursor::IsNull() const
    {
        return clang_Cursor_isNull(cursor_) != 0;
    }

    bool Cursor::IsDefinition() const
    {
        return clang_isCursorDefinition(cursor_) != 0;
    }

    bool Cursor::IsOfKind(CXCursorKind kind) const
    {
        return cursor_.kind == kind;
    }

    CXCursorKind Cursor::GetKind() const
    {
        return cursor_.kind;
    }

    std::string Cursor::GetSpelling() const
    {
        return String(clang_getCursorSpelling(cursor_)).Get();
    }

    std::string Cursor::GetDisplayName() const
    {
        return String(clang_getCursorDisplayName(cursor_)).Get();
    }

    std::string Cursor::GetMangledName() const
    {
        return String(clang_Cursor_getMangling(cursor_)).Get();
    }

    Cursor Cursor::GetSemanticParent() const
    {
        return clang_getCursorSemanticParent(cursor_);
    }

    Cursor Cursor::GetLexicalParent() const
    {
        return clang_getCursorLexicalParent(cursor_);
    }

    SourceLocation Cursor::GetSourceLocation() const
    {
        return clang_getCursorLocation(cursor_);
    }

    std::vector<Cursor> Cursor::GetChildren() const
    {
        std::vector<Cursor> children;

        auto visitor = [](CXCursor cursor, CXCursor /*parent*/, CXClientData data)
        {
            auto container = static_cast<std::vector<Cursor>*>(data);
            container->push_back(cursor);
            return CXChildVisit_Continue;
        };

        clang_visitChildren(cursor_, visitor, &children);

        return children;
    }

    void Cursor::VisitChildren(CXCursorVisitor visitor, CXClientData data) const
    {
        clang_visitChildren(cursor_, visitor, data);
    }
}
}

#endif
