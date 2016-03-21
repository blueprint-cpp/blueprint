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
        Type GetCanonical() const;
        CXTypeKind GetKind() const;

        bool IsOfKind(CXTypeKind kind) const;
        bool IsBuiltInType() const;

        String GetSpelling() const;
        static String GetKindSpelling(CXTypeKind kind);

        uint64_t GetTypeId() const;

        size_t GetSizeOf() const;
        size_t GetOffsetOf(const std::string& fieldName) const;

    private:
        CXType type_;
    };
}
}

#endif
