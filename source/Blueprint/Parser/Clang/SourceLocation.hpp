#pragma once

#if defined(EXTERN_CLANG_ENABLED)

#include <clang-c/Index.h>
#include <filesystem/path.h>

namespace blueprint
{
namespace clang
{
    class SourceLocation
    {
    public:
        SourceLocation(CXSourceLocation sourceLocation);

        const filesystem::path& GetFile() const;
        size_t GetLine() const;
        size_t GetColumn() const;
        size_t GetOffset() const;

        std::string ToString() const;

    private:
        CXSourceLocation sourceLocation_;

        filesystem::path file_;
        size_t line_{0};
        size_t column_{0};
        size_t offset_{0};
    };
}
}

#endif
