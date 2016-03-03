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

        sourceFile_ = ToString(clang_getFileName(file));
        line_ = line;
        column_ = column;
    }

    const filesystem::path& SourceLocation::GetSourceFile() const
    {
        return sourceFile_;
    }

    size_t SourceLocation::GetLine() const
    {
        return line_;
    }

    size_t SourceLocation::GetColumn() const
    {
        return column_;
    }

    std::string SourceLocation::ToString() const
    {
        return sourceFile_.filename() + " (" + std::to_string(line_) + ":" + std::to_string(column_) + ")";
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
