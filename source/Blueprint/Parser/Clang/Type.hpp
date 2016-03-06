#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Clang/String.hpp"

namespace blueprint
{
namespace clang
{
    class Type
    {
    public:
        Type(CXType type)
            : type_(type)
        {}

        explicit operator CXType() const
        {
            return type_;
        }

    public:
        bool IsOfKind(CXTypeKind kind) const;
        CXTypeKind GetKind() const;

        String GetSpelling() const;

    private:
        CXType type_;
    };
}
}

#endif
