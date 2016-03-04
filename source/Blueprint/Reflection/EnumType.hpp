#pragma once

#include "Blueprint/Reflection/Type.hpp"

namespace blueprint
{
namespace reflection
{
    class EnumType : public Type
    {
    public:
        using Entry = std::pair<std::string, int>;
        using Entries = std::vector<Entry>;

        void AddEntry(const std::string& name, int value);
        const Entries& GetEntries() const;

    private:
        Entries entries_;
    };
}
}
