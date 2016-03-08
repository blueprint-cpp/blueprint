#include "Blueprint/Parser/Clang/TranslationUnit.hpp"

#if defined(EXTERN_CLANG_ENABLED)

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
}
}

#endif
