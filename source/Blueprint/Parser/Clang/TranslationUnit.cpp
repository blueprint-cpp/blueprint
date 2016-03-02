#include "Blueprint/Parser/Clang/TranslationUnit.hpp"

namespace blueprint
{
namespace clang
{
    TranslationUnit::TranslationUnit(CXTranslationUnit translationUnit)
        : translationUnit_(translationUnit)
    {}

    TranslationUnit::~TranslationUnit()
    {
        clang_disposeTranslationUnit(translationUnit_);
    }

    bool TranslationUnit::IsValid() const
    {
        return translationUnit_ != nullptr;
    }

    Cursor TranslationUnit::GetCursor() const
    {
        return IsValid()
            ? clang_getTranslationUnitCursor(translationUnit_)
            : clang_getNullCursor();
    }
}
}
