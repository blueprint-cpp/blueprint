#include "Blueprint/Reflection/EnumType.hpp"

#include "Blueprint/Reflection/Visitors/TypeVisitor.hpp"

namespace blueprint
{
namespace reflection
{
    void EnumType::AddEntry(const std::string& name, size_t value)
    {
        entries_.push_back(std::make_pair(name, value));
    }

    const EnumType::Entries& EnumType::GetEntries() const
    {
        return entries_;
    }

    void EnumType::Accept(TypeVisitor& visitor) const
    {
        visitor.Visit(*this);
    }
}
}
