#include "Blueprint/Parser/Clang/TranslationUnit.hpp"

namespace blueprint
{
namespace clang
{
    TranslationUnit::TranslationUnit(CXTranslationUnit translationUnit)
        : translationUnit_(translationUnit)
    {}

    TranslationUnit::TranslationUnit(TranslationUnit&& other)
        : translationUnit_(std::move(other.translationUnit_))
    {
        other.translationUnit_ = nullptr;
    }

    TranslationUnit::~TranslationUnit()
    {
        if (translationUnit_)
        {
            clang_disposeTranslationUnit(translationUnit_);
        }
    }

    TranslationUnit& TranslationUnit::operator=(TranslationUnit&& other)
    {
        if (translationUnit_)
        {
            clang_disposeTranslationUnit(translationUnit_);
        }

        translationUnit_ = std::move(other.translationUnit_);
        other.translationUnit_ = nullptr;

        return *this;
    }

    TranslationUnit::operator CXTranslationUnit() const
    {
        return translationUnit_;
    }

    TranslationUnit::operator bool() const
    {
        return translationUnit_ != nullptr;
    }

    Cursor TranslationUnit::GetCursor() const
    {
        return translationUnit_
            ? clang_getTranslationUnitCursor(translationUnit_)
            : clang_getNullCursor();
    }

    std::vector<Diagnostic> TranslationUnit::GetDiagnostics() const
    {
        std::vector<Diagnostic> diagnostics;

        int count = clang_getNumDiagnostics(translationUnit_);

        for (int i = 0; i < count; ++i)
        {
            diagnostics.emplace_back(clang_getDiagnostic(translationUnit_, i));
        }

        return diagnostics;
    }
}
}
