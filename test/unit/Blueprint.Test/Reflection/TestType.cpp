#include <catch/catch.hpp>

#include "Blueprint/Reflection/Type.hpp"

TEST_CASE("TestType")
{
    using namespace blueprint::reflection;

    struct FakeType : public Type
    {
        virtual void Accept(TypeVisitor& /*visitor*/) const override {}
    };

    FakeType type;

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

    SECTION("Size")
    {
        type.SetSize(69);
        CHECK(type.GetSize() == 69);

        type.SetSize(1337);
        CHECK(type.GetSize() == 1337);
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

    SECTION("SourceLocation")
    {
        SourceLocation locationA;
        locationA.SetFile("file_A");
        locationA.SetLine(11);
        locationA.SetColumn(22);

        type.SetSourceLocation(locationA);
        CHECK(type.GetSourceLocation().ToString() == "file_A (11:22)");

        SourceLocation locationB;
        locationB.SetFile("file_B");
        locationB.SetLine(33);
        locationB.SetColumn(44);

        type.SetSourceLocation(locationB);
        CHECK(type.GetSourceLocation().ToString() == "file_B (33:44)");
    }
}
