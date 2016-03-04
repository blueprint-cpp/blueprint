#include "Blueprint/Reflection/EnumType.hpp"

namespace blueprint
{
namespace reflection
{
    void EnumType::AddEntry(const std::string& name, int value)
    {
        entries_.push_back(std::make_pair(name, value));
    }

    const EnumType::Entries& EnumType::GetEntries() const
    {
        return entries_;
    }
}
}
