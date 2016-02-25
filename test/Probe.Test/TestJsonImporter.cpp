#include "catch/catch.hpp"
#include "json/json.hpp"

#include "Probe/JsonImporter.hpp"

TEST_CASE("TestJsonImporter")
{
    SECTION("invalid solution")
    {
        auto invalid = probe::JsonImporter::ImportSolution("invalid.sln.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("invalid project")
    {
        auto invalid = probe::JsonImporter::ImportProject("invalid.prj.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("test_A")
    {
        auto solution = probe::JsonImporter::ImportSolution("test_A.sln.json");

        REQUIRE(solution != nullptr);

        CHECK(solution->GetName() == "test_A");
        CHECK(solution->GetProjects().empty() == true);
    }

    SECTION("test_B")
    {
        auto solution = probe::JsonImporter::ImportSolution("test_B.sln.json");

        REQUIRE(solution != nullptr);

        CHECK(solution->GetName() == "test_B");

        auto& projects = solution->GetProjects();
        REQUIRE(projects.size() == 1);

        auto project = projects[0].get();
        REQUIRE(project != nullptr);

        CHECK(project->GetName() == "test_B1");

        auto& files = project->GetFiles();
        REQUIRE(files.size() == 4);
        CHECK(files[0] == "../folder_A/sub_folder_AA/file_AA1.cpp");
        CHECK(files[1] == "../folder_A/sub_folder_AB/file_AB1.cpp");
        CHECK(files[2] == "../folder_B/file_B1.cpp");
        CHECK(files[3] == "../file_at_root.cpp");
    }

    SECTION("test_C")
    {
        auto solution = probe::JsonImporter::ImportSolution("test_C.sln.json");

        REQUIRE(solution != nullptr);

        CHECK(solution->GetName() == "test_C");

        auto& projects = solution->GetProjects();

        REQUIRE(projects.size() == 3);

        CHECK(projects[0]->GetName() == "test_C1");
        CHECK(projects[1]->GetName() == "test_C2");
        CHECK(projects[2]->GetName() == "test_C3");
    }
}
