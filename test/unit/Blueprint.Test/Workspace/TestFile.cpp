#include <catch/catch.hpp>

#include "Blueprint/Workspace/File.hpp"
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
