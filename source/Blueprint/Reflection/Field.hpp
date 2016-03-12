#pragma once

#include <string>

namespace blueprint
{
namespace reflection
{
    class Field
    {
    public:
        void SetName(const std::string& name);
        const std::string& GetName() const;

        void SetSize(size_t size);
        size_t GetSize() const;

        void SetOffset(size_t offset);
        size_t GetOffset() const;

    private:
        std::string name_;

        size_t size_{0};
        size_t offset_{0};
    };
}
}
