#include "Blueprint/Parser/Clang/Type.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    Type Type::GetCanonical() const
    {
        return clang_getCanonicalType(type_);
    }

    CXTypeKind Type::GetKind() const
    {
        return type_.kind;
    }

    bool Type::IsOfKind(CXTypeKind kind) const
    {
        return type_.kind == kind;
    }

    bool Type::IsBuiltInType() const
    {
        return type_.kind >= CXType_FirstBuiltin && type_.kind <= CXType_LastBuiltin;
    }

    String Type::GetSpelling() const
    {
        return clang_getTypeSpelling(type_);
    }

    String Type::GetKindSpelling(CXTypeKind kind)
    {
        return clang_getTypeKindSpelling(kind);
    }

    uint64_t Type::GetTypeId() const
    {
        std::hash<std::string> hashFunctor;
        return hashFunctor(GetSpelling().Get());
    }

    size_t Type::GetSizeOf() const
    {
        return clang_Type_getSizeOf(type_);
    }

    size_t Type::GetOffsetOf(const std::string& fieldName) const
    {
        return clang_Type_getOffsetOf(type_, fieldName.c_str());
    }
}
}

#endif
