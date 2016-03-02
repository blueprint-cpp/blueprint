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
        Namespace(const std::string& ns);
        Namespace(const std::vector<std::string>& names);

        Namespace Push(const std::string& ns) const;
        Namespace Pop() const;

        bool IsGlobal() const;
        int GetDepth() const;

        std::string ToString() const;

    private:
        static std::vector<std::string> Parse(const std::string& ns);

    private:
        std::vector<std::string> names_;
    };
}
}
