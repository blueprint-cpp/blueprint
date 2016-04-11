#include "BlueprintClang/SourceLocation.hpp"

#include "BlueprintClang/String.hpp"

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
        unsigned offset;

        clang_getSpellingLocation(sourceLocation_, &file, &line, &column, &offset);

        file_ = String(clang_getFileName(file)).Get();
        line_ = line;
        column_ = column;
        offset_ = offset;
    }

    const std::string& SourceLocation::GetFile() const
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

    size_t SourceLocation::GetOffset() const
    {
        return offset_;
    }
}
}
