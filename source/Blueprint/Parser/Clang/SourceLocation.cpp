#include "Blueprint/Parser/Clang/SourceLocation.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    SourceLocation::SourceLocation(CXSourceLocation sourceLocation)
        : sourceLocation_(sourceLocation)
    {
        CXFile file;
        unsigned line;
        unsigned column;

        clang_getSpellingLocation(sourceLocation_, &file, &line, &column, nullptr);

        file_ = ToString(clang_getFileName(file));
        line_ = line;
        column_ = column;
    }

    const filesystem::path& SourceLocation::GetFile() const
    {
        return file_;
    }

    size_t SourceLocation::GetLine() const
    {
        return line_;
    }

    size_t SourceLocation::GetColumn() const
    {
        return column_;
    }

    std::string SourceLocation::ToString(CXString string) const
    {
        std::string result = clang_getCString(string);
        clang_disposeString(string);
        return result;
    }
}
}

#endif
