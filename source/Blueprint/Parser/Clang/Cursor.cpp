#include "Blueprint/Parser/Clang/Cursor.hpp"

namespace blueprint
{
namespace clang
{
    Cursor::Cursor()
        : cursor_(clang_getNullCursor())
    {}

    Cursor::Cursor(CXCursor cursor)
        : cursor_(cursor)
    {}

    Cursor::operator CXCursor() const
    {
        return cursor_;
    }

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

    String Cursor::GetKindSpelling() const
    {
        return clang_getCursorKindSpelling(cursor_.kind);
    }

    String Cursor::GetSpelling() const
    {
        return clang_getCursorSpelling(cursor_);
    }

    String Cursor::GetDisplayName() const
    {
        return clang_getCursorDisplayName(cursor_);
    }

    String Cursor::GetMangling() const
    {
        return clang_Cursor_getMangling(cursor_);
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

    SourceRange Cursor::GetSourceRange() const
    {
        return clang_getCursorExtent(cursor_);
    }

    Type Cursor::GetType() const
    {
        return clang_getCursorType(cursor_);
    }

    size_t Cursor::GetOffsetOfField() const
    {
        assert(GetKind() == CXCursor_FieldDecl);

        // strange, clang returns the offset in bits instead of bytes...
        return clang_Cursor_getOffsetOfField(cursor_) / 8;
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

    void Cursor::DebugPrint(size_t indent, bool ignoreSystemHeaders) const
    {
        if (ignoreSystemHeaders && IsInSystemHeader())
        {
            return;
        }

        std::cout << std::string(indent, ' ') << GetKindSpelling().Get() << " : " << GetType().GetSpelling().Get();

        if (GetType().IsBuiltInType())
        {
            std::cout << " (builtin)";
        }
        else if (GetType().GetCanonical().IsBuiltInType())
        {
            std::cout << " (canonical -> " << GetType().GetCanonical().GetSpelling().Get() << ")";
        }

        std::cout << std::endl;

        for (auto& child : GetChildren())
        {
            child.DebugPrint(indent + 2);
        }
    }
}
}
