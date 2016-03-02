#include "Blueprint/Reflection/TypeRegistry.hpp"

#include "Blueprint/Reflection/TypeInfo.hpp"

#include <algorithm>

namespace blueprint
{
namespace reflection
{
    TypeRegistry::TypeRegistry() = default;
    TypeRegistry::~TypeRegistry() = default;

    void TypeRegistry::Register(std::unique_ptr<TypeInfo> type)
    {
        types_.push_back(std::move(type));
    }

    bool TypeRegistry::Contains(uint64_t typeId) const
    {
        return Find(typeId) != nullptr;
    }

    const TypeInfo* TypeRegistry::Find(uint64_t typeId) const
    {
        auto it = std::find_if(types_.begin(), types_.end(), [=](auto& type)
        {
            return type->GetTypeId() == typeId;
        });

        return it != types_.end() ? it->get() : nullptr;
    }

    size_t TypeRegistry::GetTypeCount() const
    {
        return types_.size();
    }
}
}
