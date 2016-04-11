#include "Blueprint/Database/Database.hpp"

#include "Blueprint/Database/Schema.hpp"
#include "Blueprint/Database/SqliteHelpers.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"

namespace blueprint
{
namespace database
{
    namespace internal
    {
        uint64_t GetCrc(const std::string& str)
        {
            std::hash<std::string> hashFunctor;
            return hashFunctor(str);
        }

        uint64_t InsertNamespace(sqlite3pp::database& db, const reflection::Namespace& ns)
        {
            auto crc = ns.GetCrc();

            sqlite3pp::command cmd(db, "INSERT OR IGNORE INTO Namespace (crc, namespace) VALUES (?, ?)");
            sqlite::ExecuteCommand(cmd, crc, ns.ToString());

            return crc;
        }

        uint64_t InsertSourceFile(sqlite3pp::database& db, const std::string& file)
        {
            auto crc = GetCrc(file);

            sqlite3pp::command cmd(db, "INSERT OR IGNORE INTO SourceFile (crc, file) VALUES (?, ?)");
            sqlite::ExecuteCommand(cmd, crc, file);

            return crc;
        }

        uint64_t InsertSourceLocation(sqlite3pp::database& db, const reflection::SourcePosition& position)
        {
            sqlite3pp::command cmd(db, "INSERT OR REPLACE INTO SourceLocation (line, column, offset) VALUES (?, ?, ?)");
            sqlite::ExecuteCommand(cmd, position.GetLine(), position.GetColumn(), position.GetOffset());

            return db.last_insert_rowid();
        }

        uint64_t InsertSourceRange(sqlite3pp::database& db, const reflection::SourceLocation& location)
        {
            uint64_t fileId  = InsertSourceFile(db, location.GetFile().str());
            uint64_t startId = InsertSourceLocation(db, location.GetStartPosition());
            uint64_t endId   = InsertSourceLocation(db, location.GetEndPosition());

            sqlite3pp::command cmd(db, "INSERT OR REPLACE INTO SourceRange (file, start, end) VALUES (?, ?, ?)");
            sqlite::ExecuteCommand(cmd, fileId, startId, endId);

            return db.last_insert_rowid();
        }
    }

    Database::Database(sqlite3pp::database& db)
        : db_(db)
    {}

    void Database::Initialize()
    {
        Schema schema(db_);
        schema.Initialize();
    }

    void Database::InsertTypes(const std::vector<const reflection::Type*>& types)
    {
        sqlite3pp::command cmd(db_, "INSERT OR REPLACE INTO Type (id, name, namespace, size, location) VALUES (?, ?, ?, ?, ?)");

        for (auto type : types)
        {
            auto namespaceId = internal::InsertNamespace(db_, type->GetNamespace());
            auto rangeId     = internal::InsertSourceRange(db_, type->GetSourceLocation());

            sqlite::ExecuteCommand(cmd, type->GetTypeId(), type->GetName(), namespaceId, type->GetSize(), rangeId);
        }
    }
}
}
