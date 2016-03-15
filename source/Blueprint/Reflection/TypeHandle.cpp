#include "Blueprint/Reflection/TypeHandle.hpp"

#include "Blueprint/Reflection/TypeRegistry.hpp"

namespace blueprint
{
namespace reflection
{
    TypeHandle::TypeHandle(uint64_t typeId)
        : typeId_(typeId)
    {}

    uint64_t TypeHandle::GetTypeId() const
    {
        return typeId_;
    }

    const Type* TypeHandle::GetType() const
    {
        auto registry = TypeRegistry::GetInstance();
        return registry ? registry->Find(typeId_) : nullptr;
    }
}
}
