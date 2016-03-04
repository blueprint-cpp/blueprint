#include "Blueprint/Parser/Clang/String.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    String::String(CXString string)
        : string_(string)
    {}

    String::~String()
    {
        clang_disposeString(string_);
    }

    std::string String::Get()
    {
        return clang_getCString(string_);
    }
}
}

#endif
