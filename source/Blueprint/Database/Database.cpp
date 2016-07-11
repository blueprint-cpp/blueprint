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
            uint64_t fileId  = InsertSourceFile(db, location.GetFile());
            uint64_t startId = InsertSourceLocation(db, location.GetStartPosition());
            uint64_t endId   = InsertSourceLocation(db, location.GetEndPosition());

            sqlite3pp::command cmd(db, "INSERT OR REPLACE INTO SourceRange (file, start, end) VALUES (?, ?, ?)");
            sqlite::ExecuteCommand(cmd, fileId, startId, endId);

            return db.last_insert_rowid();
        }
    }

    class Database::Impl
    {
    public:
        sqlite3pp::database& GetDatabase()
        {
            return database_;
        }

    private:
        sqlite3pp::database database_;
    };

    Database::Database()
        : pimpl_(std::make_unique<Impl>())
    {}

    Database::~Database() = default;

    sqlite3pp::database& Database::GetDB()
    {
        return pimpl_->GetDatabase();
    }

    void Database::Initialize(const filesystem::path& file)
    {
        auto& db = pimpl_->GetDatabase();

        db.connect(file.str().c_str(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

        Schema schema(db);
        schema.Initialize();
    }

    void Database::InsertTypes(const std::vector<const reflection::Type*>& types)
    {
        auto& db = pimpl_->GetDatabase();

        sqlite3pp::transaction transaction(db);
        sqlite3pp::command cmd(db, "INSERT OR REPLACE INTO Type (id, name, namespace, size, location) VALUES (?, ?, ?, ?, ?)");

        for (auto type : types)
        {
            auto namespaceId = internal::InsertNamespace(db, type->GetNamespace());
            auto rangeId     = internal::InsertSourceRange(db, type->GetSourceLocation());

            sqlite::ExecuteCommand(cmd, type->GetTypeId(), type->GetName(), namespaceId, type->GetSize(), rangeId);
        }

        transaction.commit();
    }
}
}
