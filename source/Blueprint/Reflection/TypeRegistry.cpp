#include "Blueprint/Reflection/TypeRegistry.hpp"

#include "Blueprint/Reflection/Visitors/TypeVisitor.hpp"
#include "Blueprint/Reflection/Type.hpp"

namespace blueprint
{
namespace reflection
{
    TypeRegistry* TypeRegistry::instance_ = nullptr;

    TypeRegistry::TypeRegistry()
    {
        instance_ = this;
    }

    TypeRegistry::~TypeRegistry()
    {
        instance_ = nullptr;
    }

    void TypeRegistry::Register(std::unique_ptr<Type> type)
    {
        types_[type->GetTypeId()] = std::move(type);
    }

    bool TypeRegistry::Contains(uint64_t typeId) const
    {
        return types_.find(typeId) != types_.end();
    }

    const Type* TypeRegistry::Find(const std::string& type) const
    {
        for (auto& kv : types_)
        {
            if (kv.second->GetFullName() == type)
            {
                return kv.second.get();
            }
        }

        return nullptr;
    }

    const Type* TypeRegistry::Find(uint64_t typeId) const
    {
        auto it = types_.find(typeId);
        return it != types_.end() ? it->second.get() : nullptr;
    }

    size_t TypeRegistry::GetTypeCount() const
    {
        return types_.size();
    }

    void TypeRegistry::Accept(TypeVisitor& visitor) const
    {
        visitor.Visit(*this);

        for (auto& kv : types_)
        {
            kv.second->Accept(visitor);
        }
    }
}
}
