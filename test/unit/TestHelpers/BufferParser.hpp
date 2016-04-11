#pragma once

#include "BlueprintClang/Index.hpp"

namespace blueprint
{
namespace unittest
{
    class BufferParser
    {
    public:
        clang::TranslationUnit Parse(const std::string& buffer);

        clang::Cursor FindChildOfKind(const clang::Cursor& cursor, CXCursorKind kind);

    private:
        CXUnsavedFile unsavedFile_;
        clang::Index index_;
    };
}
}
