#pragma once

#include <memory>
#include <unordered_map>

namespace blueprint
{
namespace reflection
{
    class Type;

    class TypeRegistry
    {
    public:
        TypeRegistry();
        ~TypeRegistry();

        void Register(std::unique_ptr<Type> type);

        bool Contains(uint64_t typeId) const;
        const Type* Find(uint64_t typeId) const;

        size_t GetTypeCount() const;

        void Dump() const;

    private:
        std::unordered_map<uint64_t, std::unique_ptr<Type>> types_;
    };
}
}
