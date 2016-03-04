#include <catch/catch.hpp>

#include "Blueprint/Reflection/EnumType.hpp"

TEST_CASE("TestEnumType")
{
    using namespace blueprint::reflection;

    EnumType enumType;

    SECTION("Default State")
    {
        CHECK(enumType.GetEntries().empty());
    }

    SECTION("Entries")
    {
        enumType.AddEntry("entry_A", 0xA);
        REQUIRE(enumType.GetEntries().size() == 1);
        CHECK(enumType.GetEntries()[0].first == "entry_A");
        CHECK(enumType.GetEntries()[0].second == 0xA);

        enumType.AddEntry("entry_B", 0xB);
        REQUIRE(enumType.GetEntries().size() == 2);
        CHECK(enumType.GetEntries()[1].first == "entry_B");
        CHECK(enumType.GetEntries()[1].second == 0xB);
    }
}
