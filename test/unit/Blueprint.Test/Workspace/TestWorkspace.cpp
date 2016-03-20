#include <catch/catch.hpp>

#include "Blueprint/Workspace/Workspace.hpp"
#include "TestHelpers/FileSystem.hpp"

using namespace blueprint;

TEST_CASE("TestWorkspace")
{
    Workspace workspace;

    SECTION("Default State")
    {
        CHECK(workspace.GetName() == "");
        CHECK(workspace.GetFile().empty());
        CHECK(workspace.GetProjects().empty());
    }

    SECTION("Name")
    {
        workspace.SetName("some_name");
        CHECK(workspace.GetName() == "some_name");

        workspace.SetName("some_other_name");
        CHECK(workspace.GetName() == "some_other_name");
    }

    SECTION("File")
    {
        workspace.SetFile("some/file");
        CHECK(NormalizedPath(workspace.GetFile()) == "some/file");

        workspace.SetFile("some/other/file");
        CHECK(NormalizedPath(workspace.GetFile()) == "some/other/file");
    }

    SECTION("Projects")
    {
        auto projectA = std::make_unique<Project>();
        auto projectB = std::make_unique<Project>();

        projectA->SetName("prj_A");
        workspace.AddProject(std::move(projectA));

        REQUIRE(workspace.GetProjects().size() == 1);
        CHECK(workspace.GetProjects()[0]->GetName() == "prj_A");

        projectB->SetName("prj_B");
        workspace.AddProject(std::move(projectB));

        REQUIRE(workspace.GetProjects().size() == 2);
        CHECK(workspace.GetProjects()[1]->GetName() == "prj_B");

        workspace.AddProject(nullptr);
        CHECK(workspace.GetProjects().size() == 2);
    }
}
