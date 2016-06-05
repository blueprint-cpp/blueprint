#include <catch/catch.hpp>

#include "Blueprint/Utilities/FileSystem.hpp"
#include "Blueprint/Utilities/JsonImporter.hpp"
#include "Blueprint/Utilities/WorkingDirectory.hpp"
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
                return std::make_unique<blueprint::MemoryInputStream>((const uint8_t*)buffer.c_str(), buffer.length());
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
        auto invalid = JsonImporter::ImportWorkspace(fakeFileSystem, "invalid.wks.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("invalid project")
    {
        auto invalid = JsonImporter::ImportProject(fakeFileSystem, "invalid.prj.json");

        REQUIRE(invalid == nullptr);
    }

    SECTION("test_A")
    {
        const std::string test_A = R"(
            {
              "workspace": "test_A",
              "projects": []
            }
        )";

        fakeFileSystem.AddFile("test_A.wks.json", test_A);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "test_A.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_A");
        CHECK(workspace->GetFile().str() == "test_A.wks.json");
        CHECK(workspace->GetProjects().empty() == true);
    }

    SECTION("test_B")
    {
        const std::string test_B = R"(
            {
              "workspace": "test_B",
              "projects": [ "test_B1.prj.json" ]
            }
        )";

        const std::string test_B1 = R"(
            {
              "project": "test_B1",
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

        fakeFileSystem.AddFile("test_B.wks.json", test_B);
        fakeFileSystem.AddFile("test_B1.prj.json", test_B1);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "test_B.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_B");
        CHECK(workspace->GetFile().str() == "test_B.wks.json");

        auto& projects = workspace->GetProjects();
        REQUIRE(projects.size() == 1);

        auto project = projects[0].get();
        REQUIRE(project != nullptr);

        CHECK(project->GetName() == "test_B1");
        CHECK(project->GetFile().str() == "test_B1.prj.json");

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

        auto& sources = project->GetSources();
        REQUIRE(sources.size() == 4);
        CHECK(sources[0] == "../folder_A/sub_folder_AA/file_AA1.cpp");
        CHECK(sources[1] == "../folder_A/sub_folder_AB/file_AB1.cpp");
        CHECK(sources[2] == "../folder_B/file_B1.cpp");
        CHECK(sources[3] == "../file_at_root.cpp");
    }

    SECTION("test_C")
    {
        const std::string test_C = R"(
            {
              "workspace": "test_C",
              "projects": [
                "test_C1.prj.json",
                "test_C2.prj.json",
                "test_C3.prj.json"
              ]
            }
        )";

        const std::string test_C1 = R"(
            {
              "project": "test_C1"
            }
        )";

        const std::string test_C2 = R"(
            {
              "project": "test_C2"
            }
        )";

        const std::string test_C3 = R"(
            {
              "project": "test_C3"
            }
        )";

        fakeFileSystem.AddFile("test_C.wks.json", test_C);
        fakeFileSystem.AddFile("test_C1.prj.json", test_C1);
        fakeFileSystem.AddFile("test_C2.prj.json", test_C2);
        fakeFileSystem.AddFile("test_C3.prj.json", test_C3);

        auto workspace = JsonImporter::ImportWorkspace(fakeFileSystem, "test_C.wks.json");

        REQUIRE(workspace != nullptr);

        CHECK(workspace->GetName() == "test_C");
        CHECK(workspace->GetFile().str() == "test_C.wks.json");

        auto& projects = workspace->GetProjects();

        REQUIRE(projects.size() == 3);

        CHECK(projects[0]->GetName() == "test_C1");
        CHECK(projects[1]->GetName() == "test_C2");
        CHECK(projects[2]->GetName() == "test_C3");

        CHECK(projects[0]->GetFile().str() == "test_C1.prj.json");
        CHECK(projects[1]->GetFile().str() == "test_C2.prj.json");
        CHECK(projects[2]->GetFile().str() == "test_C3.prj.json");
    }
}
