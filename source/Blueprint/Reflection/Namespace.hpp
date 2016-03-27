#pragma once

#include <string>
#include <vector>

namespace blueprint
{
namespace reflection
{
    class Namespace
    {
    public:
        Namespace() = default;
        Namespace(const char* ns);
        Namespace(const std::string& ns);
        explicit Namespace(const std::vector<std::string>& names);

        Namespace Push(const std::string& ns) const;
        Namespace Pop() const;

        bool IsGlobal() const;
        size_t GetDepth() const;
        uint64_t GetCrc() const;

        std::string ToString() const;

    private:
        static std::vector<std::string> Parse(const std::string& ns);

    private:
        std::vector<std::string> names_;
    };
}
}
