#include "Blueprint/Parser/Clang/String.hpp"

#if defined(EXTERN_CLANG_ENABLED)

namespace blueprint
{
namespace clang
{
    String::String()
        : string_{ nullptr, 0 }
    {}

    String::String(CXString string)
        : string_(string)
    {}

    String::String(String&& other)
        : string_(std::move(other.string_))
    {
        other.string_ = { nullptr, 0 };
    }

    String::~String()
    {
        if (string_.data)
        {
            clang_disposeString(string_);
        }
    }

    String& String::operator=(String&& other)
    {
        if (string_.data)
        {
            clang_disposeString(string_);
        }

        string_ = std::move(other.string_);
        other.string_ = { nullptr, 0 };

        return *this;
    }

    std::string String::Get()
    {
        return clang_getCString(string_);
    }
}
}

#endif
