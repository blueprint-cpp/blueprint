#pragma once

#include "Blueprint/Parser/Clang/Cursor.hpp"
#include "Blueprint/Parser/Clang/Diagnostic.hpp"

namespace blueprint
{
namespace clang
{
    class TranslationUnit
    {
    public:
        TranslationUnit() = default;
        TranslationUnit(CXTranslationUnit translationUnit);
        TranslationUnit(TranslationUnit&& other);
        ~TranslationUnit();

        TranslationUnit& operator=(TranslationUnit&& other);

        operator CXTranslationUnit() const;
        operator bool() const;

    public:
        Cursor GetCursor() const;

        std::vector<Diagnostic> GetDiagnostics() const;

    private:
        CXTranslationUnit translationUnit_{nullptr};
    };
}
}
