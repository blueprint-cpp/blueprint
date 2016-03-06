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
}
}

#endif
