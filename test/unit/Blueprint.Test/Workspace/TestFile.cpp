#include <catch/catch.hpp>

#include "Blueprint/Workspace/File.hpp"
#include "Blueprint/Workspace/FileManager.hpp"
#include "Blueprint.Test/FakeFileSystem.hpp"
#include "TestHelpers/FileSystem.hpp"

using namespace blueprint;

TEST_CASE("TestFile")
{
    File file;

    SECTION("Default State")
    {
        CHECK(file.GetFile().empty());
        CHECK(file.GetDependencies().empty());
        CHECK(file.IsSource() == false);
        CHECK(file.IsHeader() == false);
    }

    SECTION("File")
    {
        file.SetFile("some/file");
        CHECK(NormalizedPath(file.GetFile()) == "some/file");

        file.SetFile("some/other/file");
        CHECK(NormalizedPath(file.GetFile()) == "some/other/file");
    }

    SECTION("Dependencies")
    {
        SECTION("Adding")
        {
            auto dependencyA = std::make_shared<File>();
            auto dependencyB = std::make_shared<File>();

            file.AddDependency(dependencyA);

            REQUIRE(file.GetDependencies().size() == 1);
            CHECK(file.GetDependencies()[0] == dependencyA);

            file.AddDependency(dependencyB);
            REQUIRE(file.GetDependencies().size() == 2);
            CHECK(file.GetDependencies()[0] == dependencyA);
            CHECK(file.GetDependencies()[1] == dependencyB);
        }

        SECTION("Reading from a file")
        {
            const std::string buffer = R"(
                some_file.o: path_A/file_A.hpp \
                path_B/file_B.hpp \
                file_C.hpp
            )";

            unittest::FakeFileSystem fakeFileSystem;
            fakeFileSystem.AddFile("some_file.dep", buffer);

            FileManager fileManager(fakeFileSystem);

            file.ReadDependencies(fileManager, "some_file.dep");

            REQUIRE(file.GetDependencies().size() == 3);
            CHECK(file.GetDependencies()[0]->GetFile().str() == "path_A/file_A.hpp");
            CHECK(file.GetDependencies()[1]->GetFile().str() == "path_B/file_B.hpp");
            CHECK(file.GetDependencies()[2]->GetFile().str() == "file_C.hpp");
        }
    }

    SECTION("Source")
    {
        file.SetFile("file.c");
        CHECK(file.IsSource() == true);
        CHECK(file.IsHeader() == false);

        file.SetFile("file.cc");
        CHECK(file.IsSource() == true);
        CHECK(file.IsHeader() == false);

        file.SetFile("file.cpp");
        CHECK(file.IsSource() == true);
        CHECK(file.IsHeader() == false);
    }

    SECTION("Header")
    {
        file.SetFile("file.h");
        CHECK(file.IsHeader() == true);
        CHECK(file.IsSource() == false);

        file.SetFile("file.hh");
        CHECK(file.IsHeader() == true);
        CHECK(file.IsSource() == false);

        file.SetFile("file.hpp");
        CHECK(file.IsHeader() == true);
        CHECK(file.IsSource() == false);
    }
}
