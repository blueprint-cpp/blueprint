#pragma once

#include "BlueprintClang/TranslationUnit.hpp"

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

        CXErrorCode ParseSourceFile(const std::string& file, const std::vector<std::string>& arguments, unsigned options, TranslationUnit& translationUnit) const;

    private:
        CXIndex index_;
    };
}
}
