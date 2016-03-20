#include <catch/catch.hpp>

#if defined(EXTERN_CLANG_ENABLED)

#include "Blueprint/Parser/Session.hpp"
#include "TestHelpers/FileSystem.hpp"

TEST_CASE("TestSession")
{
    blueprint::Session session;

    SECTION("Default State")
    {
        CHECK(session.GetWorkspace().empty());
        CHECK(session.GetOutputDirectory().empty());
        CHECK(session.GetArguments().empty());
    }

    SECTION("Workspace")
    {
        session.SetWorkspace("some/file");
        CHECK(NormalizedPath(session.GetWorkspace()) == "some/file");

        session.SetWorkspace("some/other/file");
        CHECK(NormalizedPath(session.GetWorkspace()) == "some/other/file");
    }

    SECTION("Output Directory")
    {
        session.SetOutputDirectory("some/directory");
        CHECK(NormalizedPath(session.GetOutputDirectory()) == "some/directory");

        session.SetOutputDirectory("some/other/directory");
        CHECK(NormalizedPath(session.GetOutputDirectory()) == "some/other/directory");
    }

    SECTION("Argument")
    {
        session.AddArgument("arg_A");

        REQUIRE(session.GetArguments().size() == 1);
        CHECK(session.GetArguments()[0] == "arg_A");

        session.AddArgument("arg_B");

        REQUIRE(session.GetArguments().size() == 2);
        CHECK(session.GetArguments()[1] == "arg_B");
    }
}

#endif
