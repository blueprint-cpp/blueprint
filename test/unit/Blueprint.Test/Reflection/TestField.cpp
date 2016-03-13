#include <catch/catch.hpp>

#include "Blueprint/Reflection/Field.hpp"

#include <sstream>

TEST_CASE("TestField")
{
    using namespace blueprint::reflection;

    SECTION("Construction")
    {
        SECTION("Default")
        {
            Field field;

            CHECK(field.GetName() == "");
            CHECK(field.GetSize() == 0);
            CHECK(field.GetOffset() == 0);
        }

        SECTION("With Params")
        {
            Field fieldA("field_A", 1, 2);

            CHECK(fieldA.GetName() == "field_A");
            CHECK(fieldA.GetSize() == 1);
            CHECK(fieldA.GetOffset() == 2);

            Field fieldB("field_B", 3, 4);

            CHECK(fieldB.GetName() == "field_B");
            CHECK(fieldB.GetSize() == 3);
            CHECK(fieldB.GetOffset() == 4);
        }
    }

    SECTION("Comparison")
    {
        Field original("field", 1, 2);
        Field same("field", 1, 2);
        Field copy(original);
        Field differentName("different", 1, 2);
        Field differentSize("field", 13, 2);
        Field differentOffset("field", 1, 13);

        SECTION("Equality")
        {
            CHECK((original == same) == true);
            CHECK((original == copy) == true);
            CHECK((original == differentName) == false);
            CHECK((original == differentSize) == false);
            CHECK((original == differentOffset) == false);
        }

        SECTION("Inequality")
        {
            CHECK((original != same) == false);
            CHECK((original != copy) == false);
            CHECK((original != differentName) == true);
            CHECK((original != differentSize) == true);
            CHECK((original != differentOffset) == true);
        }
    }

    SECTION("Accessors")
    {
        Field field;

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

    SECTION("Output Stream")
    {
        std::stringstream streamA;
        std::stringstream streamB;

        Field fieldA("field_A", 1, 2);
        Field fieldB("field_B", 3, 4);

        streamA << fieldA;
        streamB << fieldB;

        CHECK(streamA.str() == "Field(field_A, 1, 2)");
        CHECK(streamB.str() == "Field(field_B, 3, 4)");
    }
}
