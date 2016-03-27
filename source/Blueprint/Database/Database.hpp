#pragma once

#include <vector>

namespace blueprint { namespace reflection { class Type; } }
namespace blueprint { namespace reflection { class SourceLocation; } }
namespace sqlite3pp { class database; }

namespace blueprint
{
namespace database
{
    class Database
    {
    public:
        Database(sqlite3pp::database& db);

        void Initialize();

        void InsertTypes(const std::vector<const reflection::Type*>& types);

    private:
        sqlite3pp::database& db_;
    };
}
}
