#pragma once

#include <memory>
#include <vector>

namespace blueprint
{
namespace reflection
{
    class TypeInfo;

    class TypeRegistry
    {
    public:
        ~TypeRegistry();

        void Register(std::unique_ptr<TypeInfo> type);

        bool Contains(uint64_t typeId) const;
        const TypeInfo* Find(uint64_t typeId) const;

        size_t GetTypeCount() const;

    private:
        std::vector<std::unique_ptr<TypeInfo>> types_;
    };
}
}
