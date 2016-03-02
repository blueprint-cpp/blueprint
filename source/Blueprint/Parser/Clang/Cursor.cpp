#include "Blueprint/Parser/Clang/Cursor.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    Cursor::Cursor(CXCursor cursor)
        : cursor_(cursor)
    {}

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

    std::string Cursor::GetSpelling() const
    {
        return ToString(clang_getCursorSpelling(cursor_));
    }

    std::string Cursor::GetDisplayName() const
    {
        return ToString(clang_getCursorDisplayName(cursor_));
    }

    std::string Cursor::GetMangledName() const
    {
        return ToString(clang_Cursor_getMangling(cursor_));
    }

    Cursor Cursor::GetSemanticParent() const
    {
        return clang_getCursorSemanticParent(cursor_);
    }

    Cursor Cursor::GetLexicalParent() const
    {
        return clang_getCursorLexicalParent(cursor_);
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

    std::string Cursor::ToString(CXString string) const
    {
        std::string result = clang_getCString(string);
        clang_disposeString(string);
        return result;
    }

    void Cursor::VisitChildren(CXCursorVisitor visitor, CXClientData data) const
    {
        clang_visitChildren(cursor_, visitor, data);
    }
}
}

#endif
