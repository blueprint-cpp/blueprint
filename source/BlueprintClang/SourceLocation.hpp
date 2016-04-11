#pragma once

#include <clang-c/Index.h>

namespace blueprint
{
namespace clang
{
    class SourceLocation
    {
    public:
        SourceLocation(CXSourceLocation sourceLocation);

        const std::string& GetFile() const;
        size_t GetLine() const;
        size_t GetColumn() const;
        size_t GetOffset() const;

        std::string ToString() const;

    private:
        CXSourceLocation sourceLocation_;

        std::string file_;
        size_t line_{0};
        size_t column_{0};
        size_t offset_{0};
    };
}
}
