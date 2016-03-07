#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/SourceLocation.hpp"
#include "Blueprint/Parser/Clang/Type.hpp"

#include <vector>

namespace blueprint
{
namespace clang
{
    class Cursor
    {
    public:
        Cursor() = default;

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

        String GetSpelling() const;
        String GetDisplayName() const;
        String GetMangling() const;

        Cursor GetSemanticParent() const;
        Cursor GetLexicalParent() const;

        SourceLocation GetSourceLocation() const;
        Type GetType() const;

        std::vector<Cursor> GetChildren() const;

        void VisitChildren(CXCursorVisitor visitor, CXClientData data) const;

    private:
        CXCursor cursor_;
    };
}
}

#endif
