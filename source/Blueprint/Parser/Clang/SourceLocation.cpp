#include "Blueprint/Parser/Clang/SourceLocation.hpp"

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/String.hpp"

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

        file_ = String(clang_getFileName(file)).Get();
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
}
}

#endif
