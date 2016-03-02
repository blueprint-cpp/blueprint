#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/Cursor.hpp"

namespace blueprint
{
namespace clang
{
    class TranslationUnit
    {
    public:
        TranslationUnit(CXTranslationUnit translationUnit);
        ~TranslationUnit();

        bool IsValid() const;

        Cursor GetCursor() const;

    private:
        CXTranslationUnit translationUnit_;
    };
}
}

#endif
