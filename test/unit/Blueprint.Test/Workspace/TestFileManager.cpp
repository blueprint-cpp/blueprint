#include <catch/catch.hpp>

#include "Blueprint/Workspace/File.hpp"
#include "Blueprint/Workspace/FileManager.hpp"
#include "Blueprint.Test/FakeFileSystem.hpp"

using namespace blueprint;

TEST_CASE("TestFileManager")
{
    unittest::FakeFileSystem fakeFileSystem;
    FileManager fileManager(fakeFileSystem);

    SECTION("FileSystem")
    {
        CHECK(&fileManager.GetFileSystem() == &fakeFileSystem);
    }

    SECTION("File")
    {
        auto fileA = fileManager.GetOrCreateFile("fileA");
        auto fileB = fileManager.GetOrCreateFile("fileB");

        REQUIRE(fileA.get() != nullptr);
        REQUIRE(fileB.get() != nullptr);

        CHECK(fileA->GetFile().str() == "fileA");
        CHECK(fileB->GetFile().str() == "fileB");

        SECTION("Subsequent calls returns the same file")
        {
            auto sameFileA = fileManager.GetOrCreateFile("fileA");
            auto sameFileB = fileManager.GetOrCreateFile("fileB");

            CHECK(sameFileA == fileA);
            CHECK(sameFileB == fileB);
        }
    }

    SECTION("Gather files")
    {
        auto fileA = fileManager.GetOrCreateFile("fileA");
        auto fileB = fileManager.GetOrCreateFile("fileB");

        std::vector<const File*> files;
        fileManager.GatherFiles(files);

        REQUIRE(files.size() == 2);
        CHECK(files[0] == fileA.get());
        CHECK(files[1] == fileB.get());
    }
}
