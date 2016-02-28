#include <catch/catch.hpp>

#include "Blueprint/Parser/CommandLineArguments.hpp"
#include "Blueprint/Workspace/Configuration.hpp"

TEST_CASE("TestCommandLineArguments")
{
    blueprint::CommandLineArguments arguments;

    SECTION("Default State")
    {
        CHECK(arguments.GetArguments().empty());
    }

    SECTION("Add")
    {
        arguments.Add("arg_A");

        REQUIRE(arguments.GetArguments().size() == 1);
        CHECK(arguments.GetArguments()[0] == "arg_A");

        arguments.Add("arg_B");

        REQUIRE(arguments.GetArguments().size() == 2);
        CHECK(arguments.GetArguments()[1] == "arg_B");
    }

    SECTION("Import Configuration")
    {
        SECTION("Invalid")
        {
            arguments.ImportConfig(nullptr, "");

            REQUIRE(arguments.GetArguments().empty());
        }

        blueprint::Configuration config;

        SECTION("Defines")
        {
            config.AddDefine("DEFINE_1");
            config.AddDefine("DEFINE_2");
            config.AddDefine("DEFINE_3");

            SECTION("No path")
            {
                arguments.ImportConfig(&config, "");

                REQUIRE(arguments.GetArguments().size() == 3);
                CHECK(arguments.GetArguments()[0] == "-DDEFINE_1");
                CHECK(arguments.GetArguments()[1] == "-DDEFINE_2");
                CHECK(arguments.GetArguments()[2] == "-DDEFINE_3");
            }

            SECTION("Path is ignored anyway")
            {
                arguments.ImportConfig(&config, "some/path");

                REQUIRE(arguments.GetArguments().size() == 3);
                CHECK(arguments.GetArguments()[0] == "-DDEFINE_1");
                CHECK(arguments.GetArguments()[1] == "-DDEFINE_2");
                CHECK(arguments.GetArguments()[2] == "-DDEFINE_3");
            }
        }

        SECTION("Includes")
        {
            config.AddInclude("include/path_A");
            config.AddInclude("include/path_B");

            SECTION("No path")
            {
                arguments.ImportConfig(&config, "");

                REQUIRE(arguments.GetArguments().size() == 2);
                CHECK(arguments.GetArguments()[0] == "-Iinclude/path_A");
                CHECK(arguments.GetArguments()[1] == "-Iinclude/path_B");
            }

            SECTION("With path")
            {
                arguments.ImportConfig(&config, "some/path/");

                REQUIRE(arguments.GetArguments().size() == 2);
                CHECK(arguments.GetArguments()[0] == "-Isome/path/include/path_A");
                CHECK(arguments.GetArguments()[1] == "-Isome/path/include/path_B");
            }
        }
    }
}
