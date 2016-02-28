#include <catch/catch.hpp>

#include "Probe/Workspace/JsonImporter.hpp"

#include <json/json.hpp>

TEST_CASE("TestJsonImporter")
{
    SECTION("invalid workspace")
    {
        auto invalid = probe::JsonImporter::ImportWorkspace("Samples/invalid.wks.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("invalid project")
    {
        auto invalid = probe::JsonImporter::ImportProject("Samples/invalid.prj.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("test_A")
    {
        auto workspace = probe::JsonImporter::ImportWorkspace("Samples/test_A.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_A");
        CHECK(workspace->GetFile().str() == "Samples/test_A.wks.json");
        CHECK(workspace->GetProjects().empty() == true);
    }

    SECTION("test_B")
    {
        auto workspace = probe::JsonImporter::ImportWorkspace("Samples/test_B.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_B");
        CHECK(workspace->GetFile().str() == "Samples/test_B.wks.json");

        auto& projects = workspace->GetProjects();
        REQUIRE(projects.size() == 1);

        auto project = projects[0].get();
        REQUIRE(project != nullptr);

        CHECK(project->GetName() == "test_B1");
        CHECK(project->GetFile().str() == "Samples/test_B1.prj.json");

        REQUIRE(project->GetConfigurations().size() == 1);

        auto config = project->GetConfigurations()[0].get();
        REQUIRE(config != nullptr);

        CHECK(config->GetName() == "Debug");
        CHECK(config->GetPrecompiledHeader() == "../precomp.cpp");

        REQUIRE(config->GetDefines().size() == 3);
        CHECK(config->GetDefines()[0] == "DEFINE_1");
        CHECK(config->GetDefines()[1] == "DEFINE_2");
        CHECK(config->GetDefines()[2] == "DEFINE_3");

        REQUIRE(config->GetIncludes().size() == 2);
        CHECK(config->GetIncludes()[0] == "../some/include/path");
        CHECK(config->GetIncludes()[1] == "../some/other/include/path");

        auto& sources = project->GetSources();
        REQUIRE(sources.size() == 4);
        CHECK(sources[0] == "../folder_A/sub_folder_AA/file_AA1.cpp");
        CHECK(sources[1] == "../folder_A/sub_folder_AB/file_AB1.cpp");
        CHECK(sources[2] == "../folder_B/file_B1.cpp");
        CHECK(sources[3] == "../file_at_root.cpp");
    }

    SECTION("test_C")
    {
        auto workspace = probe::JsonImporter::ImportWorkspace("Samples/test_C.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_C");
        CHECK(workspace->GetFile().str() == "Samples/test_C.wks.json");

        auto& projects = workspace->GetProjects();

        REQUIRE(projects.size() == 3);

        CHECK(projects[0]->GetName() == "test_C1");
        CHECK(projects[1]->GetName() == "test_C2");
        CHECK(projects[2]->GetName() == "test_C3");

        CHECK(projects[0]->GetFile().str() == "Samples/test_C1.prj.json");
        CHECK(projects[1]->GetFile().str() == "Samples/test_C2.prj.json");
        CHECK(projects[2]->GetFile().str() == "Samples/test_C3.prj.json");
    }
}
