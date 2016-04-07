#include <catch/catch.hpp>

#include "Blueprint/Workspace/Configuration.hpp"

TEST_CASE("TestConfiguration")
{
    blueprint::Configuration config;

    SECTION("Default State")
    {
        CHECK(config.GetName() == "");
        CHECK(config.GetDefines().empty() == true);
        CHECK(config.GetIncludes().empty() == true);
        CHECK(config.GetPrecompiledHeader() == "");
        CHECK(config.HasPrecompiledHeader() == false);
    }

    SECTION("Name")
    {
        config.SetName("some_name");
        CHECK(config.GetName() == "some_name");

        config.SetName("some_other_name");
        CHECK(config.GetName() == "some_other_name");
    }

    SECTION("Precompled Header")
    {
        config.SetPrecompiledHeader("pch_1");
        CHECK(config.GetPrecompiledHeader() == "pch_1");
        CHECK(config.HasPrecompiledHeader() == true);

        config.SetPrecompiledHeader("pch_2");
        CHECK(config.GetPrecompiledHeader() == "pch_2");
        CHECK(config.HasPrecompiledHeader() == true);
    }

    SECTION("Defines")
    {
        config.AddDefine("define_A");

        REQUIRE(config.GetDefines().size() == 1);
        CHECK(config.GetDefines()[0] == "define_A");

        config.AddDefine("define_B");

        REQUIRE(config.GetDefines().size() == 2);
        CHECK(config.GetDefines()[1] == "define_B");
    }

    SECTION("Includes")
    {
        config.AddInclude("include_A");

        REQUIRE(config.GetIncludes().size() == 1);
        CHECK(config.GetIncludes()[0] == "include_A");

        config.AddInclude("include_B");

        REQUIRE(config.GetIncludes().size() == 2);
        CHECK(config.GetIncludes()[1] == "include_B");
    }
}
