#pragma once

#include <memory>
#include <unordered_map>

namespace blueprint
{
namespace reflection
{
    class Type;
    class TypeVisitor;

    class TypeRegistry
    {
    public:
        TypeRegistry();
        ~TypeRegistry();

        static bool HasInstance() { return instance_ != nullptr; }
        static TypeRegistry* GetInstance() { return instance_; }

    public:
        void Register(std::unique_ptr<Type> type);

        bool Contains(uint64_t typeId) const;

        const Type* Find(const std::string& type) const;
        const Type* Find(uint64_t typeId) const;

        size_t GetTypeCount() const;

    public:
        void Accept(TypeVisitor& visitor) const;

    private:
        std::unordered_map<uint64_t, std::unique_ptr<Type>> types_;

        static TypeRegistry* instance_;
    };
}
}
