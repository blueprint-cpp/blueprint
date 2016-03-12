#include "Blueprint/Reflection/Field.hpp"

namespace blueprint
{
namespace reflection
{
    void Field::SetName(const std::string& name)
    {
        name_ = name;
    }

    const std::string& Field::GetName() const
    {
        return name_;
    }

    void Field::SetSize(size_t size)
    {
        size_ = size;
    }

    size_t Field::GetSize() const
    {
        return size_;
    }

    void Field::SetOffset(size_t offset)
    {
        offset_ = offset;
    }

    size_t Field::GetOffset() const
    {
        return offset_;
    }
}
}
