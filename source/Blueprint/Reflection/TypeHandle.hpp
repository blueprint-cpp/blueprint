#pragma once

#include <cstdint>

namespace blueprint
{
namespace reflection
{
    class Type;

    class TypeHandle
    {
    public:
        TypeHandle() = default;
        TypeHandle(uint64_t typeId);

        uint64_t GetTypeId() const;
        const Type* GetType() const;

    public:
        uint64_t typeId_{0};
    };
}
}
