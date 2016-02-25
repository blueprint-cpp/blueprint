#include "catch/catch.hpp"

#include "Probe/Project.hpp"

TEST_CASE("TestProject")
{
    probe::Project project;

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
