#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/SourceLocation.hpp"

namespace blueprint
{
namespace clang
{
    class SourceRange
    {
    public:
        SourceRange(CXSourceRange sourceRange);

        SourceLocation GetStart() const;
        SourceLocation GetEnd() const;

        std::string ToString() const;

    private:
        CXSourceRange sourceRange_;
    };
}
}

#endif
