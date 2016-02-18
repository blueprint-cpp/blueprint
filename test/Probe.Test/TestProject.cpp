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
}
