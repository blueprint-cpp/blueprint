#pragma once

#include "Blueprint/Reflection/TypeHandle.hpp"

namespace blueprint
{
namespace reflection
{
    class Field
    {
    public:
        Field() = default;
        Field(uint64_t typeId, const std::string& name, size_t size, size_t offset);

        bool operator==(const Field& other) const;
        bool operator!=(const Field& other) const;

    public:
        void SetType(const TypeHandle& type);
        const TypeHandle& GetType() const;

        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetSize(size_t size);
        size_t GetSize() const;

        void SetOffset(size_t offset);
        size_t GetOffset() const;

    private:
        TypeHandle type_;

        std::string name_;

        size_t size_{0};
        size_t offset_{0};
    };

    std::ostream& operator<<(std::ostream& stream, const Field& field);
}
}
