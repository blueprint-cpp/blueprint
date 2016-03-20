#include "Blueprint/Reflection/TypeHandle.hpp"

#include "Blueprint/Reflection/TypeRegistry.hpp"

namespace blueprint
{
namespace reflection
{
    TypeHandle::TypeHandle(uint64_t typeId)
        : typeId_(typeId)
    {}

    bool TypeHandle::operator==(const TypeHandle& other) const
    {
        return typeId_ == other.typeId_;
    }

    bool TypeHandle::operator!=(const TypeHandle& other) const
    {
        return !(*this == other);
    }

    uint64_t TypeHandle::GetId() const
    {
        return typeId_;
    }

    const Type* TypeHandle::Get() const
    {
        auto registry = TypeRegistry::GetInstance();
        return registry ? registry->Find(typeId_) : nullptr;
    }
}
}
