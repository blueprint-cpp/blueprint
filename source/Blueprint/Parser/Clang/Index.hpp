#pragma once

#include "Blueprint/Parser/Clang/TranslationUnit.hpp"

namespace blueprint { class CommandLineArguments; }

namespace blueprint
{
namespace clang
{
    class Index
    {
    public:
        Index();
        ~Index();

        explicit operator CXIndex() const
        {
            return index_;
        }

        CXErrorCode ParseSourceFile(const std::string& file, const CommandLineArguments& arguments, unsigned options, TranslationUnit& translationUnit) const;

    private:
        CXIndex index_;
    };
}
}
