#pragma once

#include "Blueprint/Reflection/SourcePosition.hpp"

namespace blueprint
{
namespace reflection
{
    class SourceLocation
    {
    public:
        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

        void SetStartPosition(const SourcePosition& start);
        const SourcePosition& GetStartPosition() const;
        SourcePosition& GetStartPosition();

        void SetEndPosition(const SourcePosition& end);
        const SourcePosition& GetEndPosition() const;
        SourcePosition& GetEndPosition();

        std::string ToString() const;

    private:
        filesystem::path file_;

        SourcePosition start_;
        SourcePosition end_;
    };
}
}
