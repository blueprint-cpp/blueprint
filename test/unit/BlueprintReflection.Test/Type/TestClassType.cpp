#include <catch/catch.hpp>

#include "BlueprintReflection/Type/ClassType.hpp"

TEST_CASE("TestClassType")
{
    using namespace blueprint::reflection;

    ClassType classType;

    SECTION("Default State")
    {
        CHECK(classType.GetBaseClasses().empty());
        CHECK(classType.GetNestedTypes().empty());
        CHECK(classType.GetMethods().empty());
        CHECK(classType.GetFields().empty());
    }

    SECTION("Base Classes")
    {
        ClassType parentA;

        classType.AddBaseClass(&parentA);
        REQUIRE(classType.GetBaseClasses().size() == 1);
        CHECK(classType.GetBaseClasses()[0] == &parentA);

        ClassType parentB;

        classType.AddBaseClass(&parentB);
        REQUIRE(classType.GetBaseClasses().size() == 2);
        CHECK(classType.GetBaseClasses()[1] == &parentB);
    }

    SECTION("Nested Types")
    {
        SECTION("Invalid handles are ignored")
        {
            classType.AddNestedType(TypeHandle());
            CHECK(classType.GetNestedTypes().empty());

            classType.AddNestedType(0);
            CHECK(classType.GetNestedTypes().empty());
        }

        SECTION("Valid handles are added")
        {
            classType.AddNestedType(0xA);
            REQUIRE(classType.GetNestedTypes().size() == 1);
            CHECK(classType.GetNestedTypes()[0].GetId() == 0xA);

            classType.AddNestedType(0xB);
            REQUIRE(classType.GetNestedTypes().size() == 2);
            CHECK(classType.GetNestedTypes()[1].GetId() == 0xB);
        }
    }

    SECTION("Methods")
    {
        classType.AddMethod("method_A");
        REQUIRE(classType.GetMethods().size() == 1);
        CHECK(classType.GetMethods()[0] == "method_A");

        classType.AddMethod("method_B");
        REQUIRE(classType.GetMethods().size() == 2);
        CHECK(classType.GetMethods()[1] == "method_B");
    }

    SECTION("Fields")
    {
        Field fieldA(0xA, "field_A", 4, 8);

        classType.AddField(fieldA);
        REQUIRE(classType.GetFields().size() == 1);
        CHECK(classType.GetFields()[0] == fieldA);

        Field fieldB(0xB, "field_B", 12, 16);

        classType.AddField(fieldB);
        REQUIRE(classType.GetFields().size() == 2);
        CHECK(classType.GetFields()[1] == fieldB);
    }
}
