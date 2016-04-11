#include "BlueprintReflection/Type/SourceLocation.hpp"

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

    void SourceLocation::SetStartPosition(const SourcePosition& start)
    {
        start_ = start;
    }

    const SourcePosition& SourceLocation::GetStartPosition() const
    {
        return start_;
    }

    SourcePosition& SourceLocation::GetStartPosition()
    {
        return start_;
    }

    void SourceLocation::SetEndPosition(const SourcePosition& end)
    {
        end_ = end;
    }

    const SourcePosition& SourceLocation::GetEndPosition() const
    {
        return end_;
    }

    SourcePosition& SourceLocation::GetEndPosition()
    {
        return end_;
    }

    std::string SourceLocation::ToString() const
    {
        return (!file_.empty() ? file_.str(filesystem::path::posix_path) : "<invalid>")
            + " " + start_.ToString()
            + "-" + end_.ToString();
    }
}
}
