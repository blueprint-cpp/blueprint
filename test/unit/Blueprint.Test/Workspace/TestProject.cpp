#include <catch/catch.hpp>

#include "Blueprint/Workspace/File.hpp"
#include "Blueprint/Workspace/Project.hpp"
#include "TestHelpers/FileSystem.hpp"

using namespace blueprint;

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
        CHECK(NormalizedPath(project.GetFile()) == "some/file");

        project.SetFile("some/other/file");
        CHECK(NormalizedPath(project.GetFile()) == "some/other/file");
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
        auto fileA = std::make_shared<File>();
        auto fileB = std::make_shared<File>();

        project.AddFile(fileA);

        REQUIRE(project.GetFiles().size() == 1);
        CHECK(project.GetFiles()[0] == fileA);

        project.AddFile(fileB);

        REQUIRE(project.GetFiles().size() == 2);
        CHECK(project.GetFiles()[0] == fileA);
        CHECK(project.GetFiles()[1] == fileB);
    }
}
