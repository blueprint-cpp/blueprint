#pragma once

#include "BlueprintReflection/Type/Type.hpp"

namespace blueprint
{
namespace reflection
{
    class EnumType : public Type
    {
    public:
        using Entry = std::pair<std::string, size_t>;
        using Entries = std::vector<Entry>;

        void AddEntry(const std::string& name, size_t value);
        const Entries& GetEntries() const;

        virtual void Accept(TypeVisitor& visitor) const override;

    private:
        Entries entries_;
    };
}
}
