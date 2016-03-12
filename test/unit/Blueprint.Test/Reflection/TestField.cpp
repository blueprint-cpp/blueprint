#include <catch/catch.hpp>

#include "Blueprint/Reflection/Field.hpp"

TEST_CASE("TestField")
{
    using namespace blueprint::reflection;

    Field field;

    SECTION("Default State")
    {
        CHECK(field.GetName() == "");
        CHECK(field.GetSize() == 0);
        CHECK(field.GetOffset() == 0);
    }

    SECTION("Name")
    {
        field.SetName("some_name");
        CHECK(field.GetName() == "some_name");

        field.SetName("some_other_name");
        CHECK(field.GetName() == "some_other_name");
    }

    SECTION("Size")
    {
        field.SetSize(4);
        CHECK(field.GetSize() == 4);

        field.SetSize(8);
        CHECK(field.GetSize() == 8);
    }

    SECTION("Offset")
    {
        field.SetOffset(4);
        CHECK(field.GetOffset() == 4);

        field.SetOffset(8);
        CHECK(field.GetOffset() == 8);
    }
}
