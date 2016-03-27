#include "Blueprint/Database/Schema.hpp"

#include "Blueprint/Database/SqliteApi.hpp"

namespace blueprint
{
namespace database
{
    Schema::Schema(sqlite3pp::database& db)
        : db_(db)
    {}

    void Schema::Initialize()
    {
        CreateTables();
    }

    void Schema::CreateTables()
    {
        CreateSourceFile();
        CreateSourceRange();
        CreateSourceLocation();
        CreateNamespace();
        CreateType();
    }

    void Schema::CreateSourceFile()
    {
        auto sql =
            "CREATE TABLE SourceFile"
            "("
            "    crc  INTEGER PRIMARY KEY,"
            "    file TEXT"
            ")";

        db_.execute(sql);
    }

    void Schema::CreateSourceRange()
    {
        auto sql =
            "CREATE TABLE SourceRange"
            "("
            "    id    INTEGER PRIMARY KEY AUTOINCREMENT,"
            "    file  INTEGER,"
            "    start INTEGER,"
            "    end   INTEGER,"
            "    FOREIGN KEY (file)  REFERENCES SourceFile(crc)"
            "    FOREIGN KEY (start) REFERENCES SourceLocation(id)"
            "    FOREIGN KEY (end)   REFERENCES SourceLocation(id)"
            ")";

        db_.execute(sql);
    }

    void Schema::CreateSourceLocation()
    {
        auto sql =
            "CREATE TABLE SourceLocation"
            "("
            "    id     INTEGER PRIMARY KEY AUTOINCREMENT,"
            "    line   INTEGER,"
            "    column INTEGER,"
            "    offset INTEGER"
            ")";

        db_.execute(sql);
    }

    void Schema::CreateNamespace()
    {
        auto sql =
            "CREATE TABLE Namespace"
            "("
            "    crc       INTEGER PRIMARY KEY,"
            "    namespace TEXT"
            ")";

        db_.execute(sql);
    }

    void Schema::CreateType()
    {
        auto sql =
            "CREATE TABLE Type"
            "("
            "    id        INTEGER PRIMARY KEY,"
            "    name      TEXT,"
            "    namespace INTEGER,"
            "    size      INTEGER,"
            "    location  INTEGER,"
            "    FOREIGN KEY (namespace) REFERENCES Namespace(crc)"
            "    FOREIGN KEY (location)  REFERENCES SourceLocation(id)"
            ")";

        db_.execute(sql);
    }
}
}
