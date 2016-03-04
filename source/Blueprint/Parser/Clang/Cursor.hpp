#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/SourceLocation.hpp"

#include <vector>

namespace blueprint
{
namespace clang
{
    class Cursor
    {
    public:
        Cursor(CXCursor cursor)
            : cursor_(cursor)
        {}

        explicit operator CXCursor() const
        {
            return cursor_;
        }

    public:
        bool IsInSystemHeader() const;
        bool IsFromMainFile() const;

        bool IsNull() const;
        bool IsDefinition() const;
        bool IsOfKind(CXCursorKind kind) const;
        CXCursorKind GetKind() const;

        std::string GetSpelling() const;
        std::string GetDisplayName() const;
        std::string GetMangledName() const;

        Cursor GetSemanticParent() const;
        Cursor GetLexicalParent() const;

        SourceLocation GetSourceLocation() const;

        std::vector<Cursor> GetChildren() const;

        void VisitChildren(CXCursorVisitor visitor, CXClientData data) const;

    private:
        std::string ToString(CXString string) const;

    private:
        CXCursor cursor_;
    };
}
}

#endif
