#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/TranslationUnit.hpp"

namespace blueprint
{
namespace clang
{
    class Index
    {
    public:
        Index();
        ~Index();

        TranslationUnit ParseSourceFile(const std::string& file, int argc, const char** argv, unsigned options) const;

    private:
        CXIndex index_;
    };
}
}

#endif
