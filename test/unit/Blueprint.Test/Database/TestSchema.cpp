#include <catch/catch.hpp>

#include "Blueprint/Database/Schema.hpp"
#include "Blueprint/Database/SqliteHelpers.hpp"

namespace
{
    size_t GetTableCount(sqlite3pp::database& db)
    {
        sqlite3pp::query query(db, "SELECT count(*) FROM sqlite_master WHERE type='table'");
        return (*query.begin()).get<int>(0);
    }

    bool ContainsTable(sqlite3pp::database& db, const std::string& table)
    {
        sqlite3pp::query query(db, "SELECT name FROM sqlite_master WHERE type='table' AND name=?");
        query.bind(1, table.c_str(), sqlite3pp::nocopy);
        return query.begin() != query.end();
    }
}

TEST_CASE("TestSchema")
{
    using namespace blueprint::database;
    using namespace blueprint::sqlite;

    SECTION("Initialize")
    {
        sqlite3pp::database db(":memory:");

        Schema schema(db);
        schema.Initialize();

        SECTION("Tables")
        {
            CHECK(GetTableCount(db) == 5);
            CHECK(ContainsTable(db, "sqlite_sequence"));
            CHECK(ContainsTable(db, "SourceFile"));
            CHECK(ContainsTable(db, "SourceLocation"));
            CHECK(ContainsTable(db, "Namespace"));
            CHECK(ContainsTable(db, "Type"));
        }

        SECTION("SourceFile")
        {
            sqlite3pp::command insert(db, "INSERT INTO SourceFile (crc, file) VALUES (?, ?)");

            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xA, "some/file"));
            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xB, "some/other/file"));

            sqlite3pp::query select(db, "SELECT * FROM SourceFile");
            REQUIRE(select.column_count() == 2);

            auto compare = [](auto row, auto arg1, auto arg2)
            {
                auto columns = row.template get_columns<int, const char*>(0, 1);
                return columns == std::make_tuple(arg1, arg2);
            };

            auto it = select.begin();
            CHECK(compare(*it,     0xA, std::string("some/file")));
            CHECK(compare(*(++it), 0xB, std::string("some/other/file")));
            REQUIRE(++it == select.end());
        }

        SECTION("SourceLocation")
        {
            sqlite3pp::command insert(db, "INSERT INTO SourceLocation (file, line, column, offset) VALUES (?, ?, ?, ?)");

            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xA, 1, 2, 3));
            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xB, 4, 5, 6));

            sqlite3pp::query select(db, "SELECT * FROM SourceLocation");
            REQUIRE(select.column_count() == 5);

            auto compare = [](auto row, auto arg1, auto arg2, auto arg3, auto arg4, auto arg5)
            {
                auto columns = row.template get_columns<int, int, int, int, int>(0, 1, 2, 3, 4);
                return columns == std::make_tuple(arg1, arg2, arg3, arg4, arg5);
            };

            auto it = select.begin();
            CHECK(compare(*it,     1, 0xA, 1, 2, 3));
            CHECK(compare(*(++it), 2, 0xB, 4, 5, 6));
            REQUIRE(++it == select.end());
        }

        SECTION("Namespace")
        {
            sqlite3pp::command insert(db, "INSERT INTO Namespace (crc, namespace) VALUES (?, ?)");

            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xA, "some::scope"));
            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xB, "some::other::scope"));

            sqlite3pp::query select(db, "SELECT * FROM Namespace");
            REQUIRE(select.column_count() == 2);

            auto compare = [](auto row, auto arg1, auto arg2)
            {
                auto columns = row.template get_columns<int, const char*>(0, 1);
                return columns == std::make_tuple(arg1, arg2);
            };

            auto it = select.begin();
            CHECK(compare(*it,     0xA, std::string("some::scope")));
            CHECK(compare(*(++it), 0xB, std::string("some::other::scope")));
            REQUIRE(++it == select.end());
        }

        SECTION("Type")
        {
            sqlite3pp::command insert(db, "INSERT INTO Type (id, name, namespace, size, location) VALUES (?, ?, ?, ?, ?)");

            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xA, "type_A", 1, 2, 3));
            CHECK(SQLITE_OK == ExecuteCommand(insert, 0xB, "type_B", 4, 5, 6));

            sqlite3pp::query select(db, "SELECT * FROM Type");
            REQUIRE(select.column_count() == 5);

            auto compare = [](auto row, auto arg1, auto arg2, auto arg3, auto arg4, auto arg5)
            {
                auto columns = row.template get_columns<int, const char*, int, int, int>(0, 1, 2, 3, 4);
                return columns == std::make_tuple(arg1, arg2, arg3, arg4, arg5);
            };

            auto it = select.begin();
            CHECK(compare(*it,     0xA, std::string("type_A"), 1, 2, 3));
            CHECK(compare(*(++it), 0xB, std::string("type_B"), 4, 5, 6));
            CHECK(++it == select.end());
        }
    }
}
