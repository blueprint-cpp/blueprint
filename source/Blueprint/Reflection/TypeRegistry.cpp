#include "Blueprint/Reflection/TypeRegistry.hpp"

#include "Blueprint/Reflection/Type.hpp"

#include <algorithm>
#include <iostream>

namespace blueprint
{
namespace reflection
{
    TypeRegistry::TypeRegistry() = default;
    TypeRegistry::~TypeRegistry() = default;

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

    void TypeRegistry::Dump() const
    {
        std::cout << std::endl;
        std::cout << "Type Registry : " << types_.size() << " types" << std::endl;
        std::cout << std::endl;

        std::vector<const Type*> types;
        types.reserve(types_.size());

        for (auto& kv : types_)
        {
            types.emplace_back(kv.second.get());
        }

        std::sort(types.begin(), types.end(), [](auto lhs, auto rhs)
        {
            return lhs->GetFullName() < rhs->GetFullName();
        });

        for (auto type : types)
        {
            //std::cout << type->GetSourceLocation().ToString() << std::endl;
            std::cout << type->GetFullName() << std::endl;
        }
    }
}
}
