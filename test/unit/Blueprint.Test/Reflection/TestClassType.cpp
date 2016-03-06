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
        classType.AddField("field_A");
        REQUIRE(classType.GetFields().size() == 1);
        CHECK(classType.GetFields()[0] == "field_A");

        classType.AddField("field_B");
        REQUIRE(classType.GetFields().size() == 2);
        CHECK(classType.GetFields()[1] == "field_B");
    }
}
