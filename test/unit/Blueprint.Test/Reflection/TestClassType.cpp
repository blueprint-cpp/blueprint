#include <catch/catch.hpp>

#include "Blueprint/Reflection/ClassType.hpp"

TEST_CASE("TestClassType")
{
    using namespace blueprint::reflection;

    ClassType classType;

    SECTION("Default State")
    {
        CHECK(classType.GetMethods().empty());
        CHECK(classType.GetFields().empty());
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
        Field fieldA("field_A", 4, 8);

        classType.AddField(fieldA);
        REQUIRE(classType.GetFields().size() == 1);
        CHECK(classType.GetFields()[0] == fieldA);

        Field fieldB("field_B", 12, 16);

        classType.AddField(fieldB);
        REQUIRE(classType.GetFields().size() == 2);
        CHECK(classType.GetFields()[1] == fieldB);
    }
}
