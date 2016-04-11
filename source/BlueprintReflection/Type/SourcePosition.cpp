#include "BlueprintReflection/Type/SourcePosition.hpp"

namespace blueprint
{
namespace reflection
{
    SourcePosition::SourcePosition(size_t line, size_t column, size_t offset)
        : line_(line)
        , column_(column)
        , offset_(offset)
    {}

    bool SourcePosition::operator==(const SourcePosition& other) const
    {
        return !(*this != other);
    }

    bool SourcePosition::operator!=(const SourcePosition& other) const
    {
        return line_ != other.line_
            || column_ != other.column_
            || offset_ != other.offset_;
    }

    void SourcePosition::SetLine(size_t line)
    {
        line_ = line;
    }

    size_t SourcePosition::GetLine() const
    {
        return line_;
    }

    void SourcePosition::SetColumn(size_t column)
    {
        column_ = column;
    }

    size_t SourcePosition::GetColumn() const
    {
        return column_;
    }

    void SourcePosition::SetOffset(size_t offset)
    {
        offset_ = offset;
    }

    size_t SourcePosition::GetOffset() const
    {
        return offset_;
    }

    std::string SourcePosition::ToString() const
    {
        return "(" + std::to_string(line_) + ":" + std::to_string(column_) + ":" + std::to_string(offset_) + ")";
    }
}
}
