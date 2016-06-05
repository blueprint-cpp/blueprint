#include <catch/catch.hpp>

#include "Blueprint/Utilities/FileSystem.hpp"
#include "Blueprint/Utilities/JsonImporter.hpp"
#include "Blueprint/Utilities/WorkingDirectory.hpp"
#include "Blueprint/Workspace/File.hpp"
#include "TestHelpers/MemoryInputStream.hpp"

#include <json/json.hpp>

namespace
{
    class FakeFileSystem : public blueprint::FileSystem
    {
    public:
        virtual std::unique_ptr<std::istream> Open(const filesystem::path& file) override
        {
            auto entry = files_.find(file.str());

            if (entry != files_.end())
            {
                auto& buffer = entry->second;
                return std::make_unique<blueprint::MemoryInputStream>((const uint8_t*)buffer.data(), buffer.length());
            }

            return nullptr;
        }

        void AddFile(const filesystem::path& file, const std::string& buffer)
        {
            files_[file.str()] = buffer;
        }

    private:
        std::map<std::string, std::string> files_;
    };
}

TEST_CASE("TestJsonImporter")
{
    using namespace blueprint;

    FakeFileSystem fakeFileSystem;

    WorkingDirectory::SetCurrent("Samples");

    SECTION("invalid workspace")
    {
        auto invalid = JsonImporter::ImportWorkspace(fakeFileSystem, "invalid.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("invalid project")
    {
        auto invalid = JsonImporter::ImportProject(fakeFileSystem, "invalid.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("empty workspace")
    {
        const std::string wksA = R"(
            {
              "workspace": "wks_A",
              "projects": []
            }
        )";

        fakeFileSystem.AddFile("wks_A.json", wksA);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "wks_A.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "wks_A");
        CHECK(workspace->GetFile().str() == "wks_A.json");
        CHECK(workspace->GetProjects().empty() == true);
    }

    SECTION("workspace with projects")
    {
        const std::string wksB = R"(
            {
              "workspace": "wks_B",
              "projects": [ "prj_B1.json", "prj_B2.json", "prj_B3.json" ]
            }
        )";

        const std::string prjB1 = R"(
            {
              "project": "prj_B1"
            }
        )";

        const std::string prjB2 = R"(
            {
              "project": "prj_B2"
            }
        )";

        const std::string prjB3 = R"(
            {
              "project": "prj_B3"
            }
        )";

        fakeFileSystem.AddFile("wks_B.json", wksB);
        fakeFileSystem.AddFile("prj_B1.json", prjB1);
        fakeFileSystem.AddFile("prj_B2.json", prjB2);
        fakeFileSystem.AddFile("prj_B3.json", prjB3);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "wks_B.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "wks_B");
        CHECK(workspace->GetFile().str() == "wks_B.json");

        auto& projects = workspace->GetProjects();

        REQUIRE(projects.size() == 3);

        CHECK(projects[0]->GetName() == "prj_B1");
        CHECK(projects[1]->GetName() == "prj_B2");
        CHECK(projects[2]->GetName() == "prj_B3");

        CHECK(projects[0]->GetFile().str() == "prj_B1.json");
        CHECK(projects[1]->GetFile().str() == "prj_B2.json");
        CHECK(projects[2]->GetFile().str() == "prj_B3.json");
    }

    SECTION("project content")
    {
        const std::string wksC= R"(
            {
              "workspace": "wks_C",
              "projects": [ "prj_C.json" ]
            }
        )";

        const std::string prjC = R"(
            {
              "project": "prj_C",
              "configs": [
                {
                  "name": "Debug",
                  "defines": [
                    "DEFINE_1",
                    "DEFINE_2",
                    "DEFINE_3"
                  ],
                  "includedirs": [
                    "../some/include/path",
                    "../some/other/include/path"
                  ],
                  "pchheader": "../precomp.hpp",
                  "pchsource": "../precomp.cpp"
                }
              ],
              "files": [
                "../folder_A/sub_folder_AA/file_AA1.cpp",
                "../folder_A/sub_folder_AB/file_AB1.cpp",
                "../folder_B/file_B1.cpp",
                "../file_at_root.cpp"
              ]
            }
        )";

        fakeFileSystem.AddFile("wks_C.json", wksC);
        fakeFileSystem.AddFile("prj_C.json", prjC);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "wks_C.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "wks_C");
        CHECK(workspace->GetFile().str() == "wks_C.json");

        auto& projects = workspace->GetProjects();
        REQUIRE(projects.size() == 1);

        auto project = projects[0].get();
        REQUIRE(project != nullptr);

        CHECK(project->GetName() == "prj_C");
        CHECK(project->GetFile().str() == "prj_C.json");

        REQUIRE(project->GetConfigurations().size() == 1);

        auto config = project->GetConfigurations()[0].get();
        REQUIRE(config != nullptr);

        CHECK(config->GetName() == "Debug");
        CHECK(config->HasPrecompiledHeader() == true);
        CHECK(config->GetPrecompiledHeader() == "../precomp.hpp");
        CHECK(config->GetPrecompiledSource() == "../precomp.cpp");

        REQUIRE(config->GetDefines().size() == 3);
        CHECK(config->GetDefines()[0] == "DEFINE_1");
        CHECK(config->GetDefines()[1] == "DEFINE_2");
        CHECK(config->GetDefines()[2] == "DEFINE_3");

        REQUIRE(config->GetIncludes().size() == 2);
        CHECK(config->GetIncludes()[0] == "../some/include/path");
        CHECK(config->GetIncludes()[1] == "../some/other/include/path");

        auto& files = project->GetFiles();
        REQUIRE(files.size() == 4);
        CHECK(files[0]->GetFile().str() == "../folder_A/sub_folder_AA/file_AA1.cpp");
        CHECK(files[1]->GetFile().str() == "../folder_A/sub_folder_AB/file_AB1.cpp");
        CHECK(files[2]->GetFile().str() == "../folder_B/file_B1.cpp");
        CHECK(files[3]->GetFile().str() == "../file_at_root.cpp");
    }
}
