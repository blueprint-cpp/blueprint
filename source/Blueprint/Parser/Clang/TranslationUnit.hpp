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

        unsigned GetDefaultSaveOptions() const;
        CXSaveError Save(const std::string& file, unsigned options) const;
        CXSaveError Save(const std::string& file) const;

    private:
        CXTranslationUnit translationUnit_{nullptr};
    };
}
}
