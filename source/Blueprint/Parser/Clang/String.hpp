#pragma once

#include <clang-c/Index.h>

namespace blueprint
{
namespace clang
{
    class String
    {
    public:
        String();
        String(CXString string);
        String(String&& other);
        ~String();

        String& operator=(String&& other);

        std::string Get();

    private:
        CXString string_;
    };
}
}
