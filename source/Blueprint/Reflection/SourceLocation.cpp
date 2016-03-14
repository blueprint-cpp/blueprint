#include "Blueprint/Reflection/SourceLocation.hpp"

namespace blueprint
{
namespace reflection
{
    void SourceLocation::SetFile(const filesystem::path& file)
    {
        file_ = file;
    }

    const filesystem::path& SourceLocation::GetFile() const
    {
        return file_;
    }

    void SourceLocation::SetLine(size_t line)
    {
        line_ = line;
    }

    size_t SourceLocation::GetLine() const
    {
        return line_;
    }

    void SourceLocation::SetColumn(size_t column)
    {
        column_ = column;
    }

    size_t SourceLocation::GetColumn() const
    {
        return column_;
    }

    std::string SourceLocation::ToString() const
    {
        std::string file = !file_.empty() ? file_.str(filesystem::path::posix_path) : "<invalid>";
        return file + " (" + std::to_string(line_) + ":" + std::to_string(column_) + ")";
    }
}
}
