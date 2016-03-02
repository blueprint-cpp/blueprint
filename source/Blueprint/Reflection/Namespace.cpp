#include "Blueprint/Reflection/Namespace.hpp"

namespace blueprint
{
namespace reflection
{
    Namespace::Namespace(const char* ns)
        : names_(Parse(ns))
    {}

    Namespace::Namespace(const std::string& ns)
        : names_(Parse(ns))
    {}

    Namespace::Namespace(const std::vector<std::string>& names)
        : names_(names)
    {}

    Namespace Namespace::Push(const std::string& ns) const
    {
        auto parsed = Parse(ns);
        auto names = names_;
        names.insert(names.end(), parsed.begin(), parsed.end());

        return Namespace(names);
    }

    Namespace Namespace::Pop() const
    {
        if (IsGlobal())
        {
            return Namespace();
        }

        auto names = names_;
        names.pop_back();

        return Namespace(names);
    }

    bool Namespace::IsGlobal() const
    {
        return names_.empty();
    }

    int Namespace::GetDepth() const
    {
        return names_.size();
    }

    std::string Namespace::ToString() const
    {
        std::string result;

        if (!names_.empty())
        {
            for (auto& name : names_)
            {
                result += !result.empty() ? "::" + name : name;
            }
        }

        return result;
    }

    std::vector<std::string> Namespace::Parse(const std::string& ns)
    {
        std::vector<std::string> names;

        size_t prev = 0;
        size_t curr = 0;

        while ((curr = ns.find("::", curr)) != std::string::npos)
        {
            names.push_back(ns.substr(prev, curr - prev));

            curr = curr + 2;
            prev = curr;
        }

        names.push_back(ns.substr(prev, curr - prev));

        return names;
    }
}
}
