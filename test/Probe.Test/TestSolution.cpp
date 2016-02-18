#include "catch/catch.hpp"

#include "Probe/Solution.hpp"

using namespace probe;

TEST_CASE("TestSolution")
{
    Solution solution;

    SECTION("Default State")
    {
        CHECK(solution.GetName() == "");
        CHECK(solution.GetProjects().empty());
    }

    SECTION("Name")
    {
        solution.SetName("some_name");
        CHECK(solution.GetName() == "some_name");

        solution.SetName("some_other_name");
        CHECK(solution.GetName() == "some_other_name");
    }

    SECTION("Projects")
    {
        auto projectA = std::make_unique<Project>();
        auto projectB = std::make_unique<Project>();

        projectA->SetName("prj_A");
        solution.AddProject(std::move(projectA));

        CHECK(solution.GetProjects().size() == 1);
        CHECK(solution.GetProjects()[0]->GetName() == "prj_A");

        projectB->SetName("prj_B");
        solution.AddProject(std::move(projectB));

        CHECK(solution.GetProjects().size() == 2);
        CHECK(solution.GetProjects()[1]->GetName() == "prj_B");
    }
}
