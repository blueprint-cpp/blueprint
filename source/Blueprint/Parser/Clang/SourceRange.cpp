#include "Blueprint/Parser/Clang/SourceRange.hpp"

#include "Blueprint/Parser/Clang/String.hpp"

namespace blueprint
{
namespace clang
{
    SourceRange::SourceRange(CXSourceRange sourceRange)
        : sourceRange_(sourceRange)
    {}

    SourceLocation SourceRange::GetStart() const
    {
        return clang_getRangeStart(sourceRange_);
    }

    SourceLocation SourceRange::GetEnd() const
    {
        return clang_getRangeEnd(sourceRange_);
    }
}
}
