#pragma once

namespace blueprint { namespace reflection { class Type; } }
namespace sqlite3pp { class database; }

namespace blueprint
{
namespace database
{
    class Database
    {
    public:
        Database();
        ~Database();

        void Initialize(const filesystem::path& file);

        void InsertTypes(const std::vector<const reflection::Type*>& types);

    public:
        sqlite3pp::database& GetDB();

    private:
        class Impl;
        std::unique_ptr<Impl> pimpl_;
    };
}
}
