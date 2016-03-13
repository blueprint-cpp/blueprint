#include "Blueprint/Parser/Clang/Type.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    bool Type::IsOfKind(CXTypeKind kind) const
    {
        return type_.kind == kind;
    }

    CXTypeKind Type::GetKind() const
    {
        return type_.kind;
    }

    String Type::GetSpelling() const
    {
        return clang_getTypeSpelling(type_);
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
