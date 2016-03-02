#include <catch/catch.hpp>

#include "Blueprint/Reflection/TypeInfo.hpp"

TEST_CASE("TestTypeInfo")
{
    using namespace blueprint::reflection;

    TypeInfo type;

    SECTION("Default State")
    {
        CHECK(type.GetTypeId() == 0);
        CHECK(type.GetName() == "");
        CHECK(type.GetNamespace().IsGlobal());
        CHECK(type.GetFullName() == "");
    }

    SECTION("Type Id")
    {
        type.SetTypeId(0xA);
        CHECK(type.GetTypeId() == 0xA);

        type.SetTypeId(0xB);
        CHECK(type.GetTypeId() == 0xB);
    }

    SECTION("Name")
    {
        type.SetName("some_name");
        CHECK(type.GetName() == "some_name");

        type.SetName("some_other_name");
        CHECK(type.GetName() == "some_other_name");
    }

    SECTION("Namespace")
    {
        type.SetNamespace("some::namespace");
        CHECK(type.GetNamespace().ToString() == "some::namespace");

        type.SetNamespace("some::other::namespace");
        CHECK(type.GetNamespace().ToString() == "some::other::namespace");
    }

    SECTION("FullName")
    {
        SECTION("only name")
        {
            type.SetName("some_name");
            CHECK(type.GetFullName() == "some_name");
        }

        SECTION("only namespace is invalid")
        {
            type.SetNamespace("some::namespace");
            CHECK(type.GetFullName() == "");
        }

        SECTION("name & namespace")
        {
            type.SetName("some_name");
            type.SetNamespace("some::namespace");
            CHECK(type.GetFullName() == "some::namespace::some_name");
        }
    }
}
