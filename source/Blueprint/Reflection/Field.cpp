#include "Blueprint/Reflection/Field.hpp"

#include <ostream>

namespace blueprint
{
namespace reflection
{
    Field::Field(const std::string& name, size_t size, size_t offset)
        : name_(name)
        , size_(size)
        , offset_(offset)
    {}

    bool Field::operator==(const Field& other) const
    {
        return !(*this != other);
    }

    bool Field::operator!=(const Field& other) const
    {
        return name_ != other.name_
            || size_ != other.size_
            || offset_ != other.offset_;
    }

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

    std::ostream& operator<<(std::ostream& stream, const Field& field)
    {
        stream << "Field(" << field.GetName() << ", " << field.GetSize() << ", " << field.GetOffset() << ")";
        return stream;
    }
}
}
