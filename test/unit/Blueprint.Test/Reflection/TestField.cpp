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

            CHECK(field.GetType().GetTypeId() == 0);
            CHECK(field.GetName() == "");
            CHECK(field.GetSize() == 0);
            CHECK(field.GetOffset() == 0);
        }

        SECTION("With Params")
        {
            Field fieldA(0xA, "field_A", 1, 2);

            CHECK(fieldA.GetType().GetTypeId() == 0xA);
            CHECK(fieldA.GetName() == "field_A");
            CHECK(fieldA.GetSize() == 1);
            CHECK(fieldA.GetOffset() == 2);

            Field fieldB(0xB, "field_B", 3, 4);

            CHECK(fieldB.GetType().GetTypeId() == 0xB);
            CHECK(fieldB.GetName() == "field_B");
            CHECK(fieldB.GetSize() == 3);
            CHECK(fieldB.GetOffset() == 4);
        }
    }

    SECTION("Comparison")
    {
        Field original(0xA, "A", 1, 2);
        Field same(0xA, "A", 1, 2);
        Field copy(original);
        Field different1(0xB, "A", 1, 2);
        Field different2(0xA, "B", 1, 2);
        Field different3(0xA, "A", 7, 2);
        Field different4(0xA, "A", 1, 7);

        SECTION("Equality")
        {
            CHECK((original == same) == true);
            CHECK((original == copy) == true);
            CHECK((original == different1) == false);
            CHECK((original == different2) == false);
            CHECK((original == different3) == false);
            CHECK((original == different4) == false);
        }

        SECTION("Inequality")
        {
            CHECK((original != same) == false);
            CHECK((original != copy) == false);
            CHECK((original != different1) == true);
            CHECK((original != different2) == true);
            CHECK((original != different3) == true);
            CHECK((original != different4) == true);
        }
    }

    SECTION("Accessors")
    {
        Field field;

        SECTION("Type")
        {
            field.SetType(0xA);
            CHECK(field.GetType().GetTypeId() == 0xA);

            field.SetType(0xB);
            CHECK(field.GetType().GetTypeId() == 0xB);
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

    SECTION("Output Stream")
    {
        std::stringstream streamA;
        std::stringstream streamB;

        Field fieldA(11, "field_A", 1, 2);
        Field fieldB(22, "field_B", 3, 4);

        streamA << fieldA;
        streamB << fieldB;

        CHECK(streamA.str() == "Field(11, field_A, 1, 2)");
        CHECK(streamB.str() == "Field(22, field_B, 3, 4)");
    }
}
