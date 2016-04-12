#pragma once

#include "BlueprintReflection/Type/SourcePosition.hpp"

namespace blueprint
{
namespace reflection
{
    class SourceLocation
    {
    public:
        void SetFile(const std::string& file);
        const std::string& GetFile() const;

        void SetStartPosition(const SourcePosition& start);
        const SourcePosition& GetStartPosition() const;
        SourcePosition& GetStartPosition();

        void SetEndPosition(const SourcePosition& end);
        const SourcePosition& GetEndPosition() const;
        SourcePosition& GetEndPosition();

        std::string ToString() const;

    private:
        std::string file_;

        SourcePosition start_;
        SourcePosition end_;
    };
}
}
