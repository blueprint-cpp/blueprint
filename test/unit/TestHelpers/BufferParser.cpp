#include "TestHelpers/BufferParser.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace unittest
{
    clang::TranslationUnit BufferParser::Parse(const std::string& buffer)
    {
        unsavedFile_.Filename = "dummy.cpp";
        unsavedFile_.Contents = buffer.c_str();
        unsavedFile_.Length   = (unsigned long)buffer.length();

        return clang_createTranslationUnitFromSourceFile(
            CXIndex(index_),
            "dummy.cpp",
            0,
            nullptr,
            1,
            &unsavedFile_);
    }

    clang::Cursor BufferParser::FindChildOfKind(const clang::Cursor& cursor, CXCursorKind kind)
    {
        for (auto& child : cursor.GetChildren())
        {
            if (child.GetKind() == kind)
            {
                return child;
            }
        }

        return clang::Cursor();
    }
}
}

#endif
