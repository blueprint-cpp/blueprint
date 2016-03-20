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

        bool operator==(const TypeHandle& other) const;
        bool operator!=(const TypeHandle& other) const;

    public:
        uint64_t GetId() const;
        const Type* Get() const;

    public:
        uint64_t typeId_{0};
    };
}
}
