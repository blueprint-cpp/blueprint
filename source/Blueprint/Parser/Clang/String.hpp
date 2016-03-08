#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include <clang-c/Index.h>

#include <string>

namespace blueprint
{
namespace clang
{
    class String
    {
    public:
        String(CXString string);
        ~String();

        std::string Get();

    private:
        CXString string_;
    };
}
}

#endif
