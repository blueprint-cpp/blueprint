#pragma once

namespace blueprint
{
namespace reflection
{
    class SourcePosition
    {
    public:
        SourcePosition() = default;
        SourcePosition(size_t line, size_t column, size_t offset);

        bool operator==(const SourcePosition& other) const;
        bool operator!=(const SourcePosition& other) const;

    public:
        void SetLine(size_t line);
        size_t GetLine() const;

        void SetColumn(size_t column);
        size_t GetColumn() const;

        void SetOffset(size_t offset);
        size_t GetOffset() const;

        std::string ToString() const;

    private:
        size_t line_{0};
        size_t column_{0};
        size_t offset_{0};
    };
}
}
