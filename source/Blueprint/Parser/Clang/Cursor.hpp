#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include <clang-c/Index.h>

#include <string>
#include <vector>

namespace blueprint
{
namespace clang
{
    class Cursor
    {
    public:
        Cursor(CXCursor cursor);

        bool IsInSystemHeader() const;
        bool IsFromMainFile() const;

        bool IsNull() const;
        bool IsDefinition() const;
        bool IsOfKind(CXCursorKind kind) const;

        std::string GetSpelling() const;
        std::string GetDisplayName() const;
        std::string GetMangledName() const;

        Cursor GetSemanticParent() const;
        Cursor GetLexicalParent() const;

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
