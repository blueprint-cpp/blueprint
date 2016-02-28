#include <catch/catch.hpp>

#include "Probe/Workspace/Project.hpp"

using namespace probe;

TEST_CASE("TestProject")
{
    Project project;

    SECTION("Default State")
    {
        CHECK(project.GetName() == "");
    }

    SECTION("Name")
    {
        project.SetName("some_name");
        CHECK(project.GetName() == "some_name");

        project.SetName("some_other_name");
        CHECK(project.GetName() == "some_other_name");
    }

    SECTION("File")
    {
        project.SetFile("some/file");
        CHECK(project.GetFile().str() == "some/file");

        project.SetFile("some/other/file");
        CHECK(project.GetFile().str() == "some/other/file");
    }

    SECTION("Configurations")
    {
        auto configA = std::make_unique<Configuration>();
        auto configB = std::make_unique<Configuration>();

        configA->SetName("config_A");
        project.AddConfiguration(std::move(configA));

        REQUIRE(project.GetConfigurations().size() == 1);
        CHECK(project.GetConfigurations()[0]->GetName() == "config_A");

        configB->SetName("config_B");
        project.AddConfiguration(std::move(configB));

        REQUIRE(project.GetConfigurations().size() == 2);
        CHECK(project.GetConfigurations()[1]->GetName() == "config_B");

        project.AddConfiguration(nullptr);
        CHECK(project.GetConfigurations().size() == 2);
    }

    SECTION("Sources")
    {
        project.AddSource("source_A");

        REQUIRE(project.GetSources().size() == 1);
        CHECK(project.GetSources()[0] == "source_A");

        project.AddSource("source_B");

        REQUIRE(project.GetSources().size() == 2);
        CHECK(project.GetSources()[1] == "source_B");
    }
}
