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
        Cursor();
        Cursor(CXCursor cursor);

        explicit operator CXCursor() const;

    public:
        bool IsInSystemHeader() const;
        bool IsFromMainFile() const;

        bool IsNull() const;
        bool IsDefinition() const;
        bool IsOfKind(CXCursorKind kind) const;
        CXCursorKind GetKind() const;
        String GetKindSpelling() const;

        String GetSpelling() const;
        String GetDisplayName() const;
        String GetMangling() const;

        Cursor GetSemanticParent() const;
        Cursor GetLexicalParent() const;

        SourceLocation GetSourceLocation() const;
        Type GetType() const;

        size_t GetOffsetOfField() const;

    public:
        std::vector<Cursor> GetChildren() const;

        void VisitChildren(CXCursorVisitor visitor, CXClientData data) const;

        void DebugPrint(size_t indent = 0, bool ignoreSystemHeaders = true) const;

    private:
        CXCursor cursor_;
    };
}
}

#endif
