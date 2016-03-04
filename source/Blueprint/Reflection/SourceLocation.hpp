#pragma once

#include <filesystem/path.h>

namespace blueprint
{
namespace reflection
{
    class SourceLocation
    {
    public:
        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

        void SetLine(size_t line);
        size_t GetLine() const;

        void SetColumn(size_t column);
        size_t GetColumn() const;

        std::string ToString() const;

    private:
        filesystem::path file_;

        size_t line_{0};
        size_t column_{0};
    };
}
}
