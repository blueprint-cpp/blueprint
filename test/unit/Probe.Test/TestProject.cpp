#include "catch/catch.hpp"

#include "Probe/Project.hpp"

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

    SECTION("Files")
    {
        project.AddFile("file_A");

        REQUIRE(project.GetFiles().size() == 1);
        CHECK(project.GetFiles()[0] == "file_A");

        project.AddFile("file_B");

        REQUIRE(project.GetFiles().size() == 2);
        CHECK(project.GetFiles()[1] == "file_B");
    }
}
