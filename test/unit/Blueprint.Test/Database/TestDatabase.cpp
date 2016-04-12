#include <catch/catch.hpp>

#include "Blueprint/Database/Database.hpp"
#include "Blueprint/Database/SqliteHelpers.hpp"
#include "BlueprintReflection/Type/ClassType.hpp"
#include "BlueprintReflection/Type/EnumType.hpp"

using namespace blueprint::reflection;
using namespace blueprint::database;
using namespace blueprint::sqlite;

namespace
{
    template<class T>
    T CreateType(uint64_t typeId, size_t size, const std::string& name, const std::string& ns)
    {
        T type;

        type.SetTypeId(typeId);
        type.SetSize(size);
        type.SetName(name);
        type.SetNamespace(ns);

        return type;
    }

    SourceLocation CreateLocation(const std::string& file, const SourcePosition& start, const SourcePosition& end)
    {
        SourceLocation location;

        location.SetFile(file);
        location.SetStartPosition(start);
        location.SetEndPosition(end);

        return location;
    }
}

TEST_CASE("TestDatabase")
{
    sqlite3pp::database db(":memory:");
    Database database(db);
    database.Initialize();

    SECTION("Insert Types")
    {
        auto typeA = CreateType<ClassType>(0xA, 11, "class_A", "");
        auto typeB = CreateType<ClassType>(0xB, 22, "class_B", "ns_1");
        auto typeC = CreateType<EnumType>(0xC, 33, "enum_C", "ns_1::ns_2");

        typeA.SetSourceLocation(CreateLocation("fileA", SourcePosition(11, 22, 33), SourcePosition(44, 55, 66)));
        typeB.SetSourceLocation(CreateLocation("some/fileB", SourcePosition(77, 88, 99), SourcePosition(11, 22, 33)));
        typeC.SetSourceLocation(CreateLocation("some/other/fileC", SourcePosition(44, 55, 66), SourcePosition(77, 88, 99)));

        database.InsertTypes({ &typeA, &typeB, &typeC });

        SECTION("Type Info")
        {
            auto sql =
                "SELECT t.id, t.size, t.name, n.namespace"
                "  FROM Type t, Namespace n"
                " WHERE t.namespace = n.crc";

            sqlite3pp::query select(db, sql);
            REQUIRE(select.column_count() == 4);

            auto compare = [](auto row, auto& type)
            {
                auto columns = row.template get_columns<int, int, const char*, const char*>(0, 1, 2, 3);

                return std::get<0>(columns) == (int)type.GetTypeId()
                    && std::get<1>(columns) == (int)type.GetSize()
                    && std::get<2>(columns) == type.GetName()
                    && std::get<3>(columns) == type.GetNamespace().ToString();
            };

            auto it = select.begin();
            CHECK(compare(*it,     typeA));
            CHECK(compare(*(++it), typeB));
            CHECK(compare(*(++it), typeC));
            REQUIRE(++it == select.end());
        }

        SECTION("Source Range")
        {
            auto sql =
                "SELECT t.location, f.file, start.line, start.column, start.offset, end.line, end.column, end.offset"
                "  FROM Type t, SourceRange sr, SourceLocation start, SourceLocation end, SourceFile f"
                " WHERE t.location == sr.id AND sr.start == start.id AND sr.end == end.id AND sr.file == f.crc";

            sqlite3pp::query select(db, sql);
            REQUIRE(select.column_count() == 8);

            auto compare = [](auto row, auto& location)
            {
                auto columns = row.template get_columns<int, const char*, int, int, int, int, int, int>(0, 1, 2, 3, 4, 5, 6, 7);

                auto& startPos = location.GetStartPosition();
                auto& endPos   = location.GetEndPosition();

                return std::get<1>(columns) == location.GetFile()
                    && std::get<2>(columns) == (int)startPos.GetLine()
                    && std::get<3>(columns) == (int)startPos.GetColumn()
                    && std::get<4>(columns) == (int)startPos.GetOffset()
                    && std::get<5>(columns) == (int)endPos.GetLine()
                    && std::get<6>(columns) == (int)endPos.GetColumn()
                    && std::get<7>(columns) == (int)endPos.GetOffset();
            };

            auto it = select.begin();
            CHECK(compare(*it,     typeA.GetSourceLocation()));
            CHECK(compare(*(++it), typeB.GetSourceLocation()));
            CHECK(compare(*(++it), typeC.GetSourceLocation()));
            REQUIRE(++it == select.end());
        }
    }
}
