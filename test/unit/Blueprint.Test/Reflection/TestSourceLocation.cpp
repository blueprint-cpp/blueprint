#include <catch/catch.hpp>

#include "Blueprint/Reflection/SourceLocation.hpp"

TEST_CASE("TestSourceLocation")
{
    using namespace blueprint::reflection;

    SourceLocation location;

    SECTION("Default State")
    {
        CHECK(location.GetFile().empty());
        CHECK(location.GetLine() == 0);
        CHECK(location.GetColumn() == 0);
        CHECK(location.ToString() == "<invalid> (0:0)");
    }

    SECTION("File")
    {
        location.SetFile("some/file");
        CHECK(location.GetFile().str() == "some/file");

        location.SetFile("some/other/file");
        CHECK(location.GetFile().str() == "some/other/file");
    }

    SECTION("Line")
    {
        location.SetLine(666);
        CHECK(location.GetLine() == 666);

        location.SetLine(1337);
        CHECK(location.GetLine() == 1337);
    }

    SECTION("Column")
    {
        location.SetColumn(666);
        CHECK(location.GetColumn() == 666);

        location.SetColumn(1337);
        CHECK(location.GetColumn() == 1337);
    }

    SECTION("ToString")
    {
        location.SetFile("some/file");
        CHECK(location.ToString() == "some/file (0:0)");

        location.SetLine(7);
        CHECK(location.ToString() == "some/file (7:0)");

        location.SetColumn(13);
        CHECK(location.ToString() == "some/file (7:13)");
    }
}
