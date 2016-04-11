-- premake5.lua

require("extern.clang")
require("extern.filesystem")
require("extern.json")
require("extern.philsquared")
require("extern.sqlite")

local usePrecompiledHeaders = true

workspace("Blueprint")
    platforms { "x64" }

    configurations { "Debug", "Release" }
        location(_ACTION)

    configuration("Debug")
        targetdir("../output/bin/Debug")
        objdir("../output/obj")
        defines { "DEBUG" }
        flags { "ExtraWarnings", "FatalWarnings", "Symbols" }

    configuration("Release")
        targetdir("../output/bin/Release")
        objdir("../output/obj")
        defines { "NDEBUG" }
        flags { "ExtraWarnings", "FatalWarnings", "Optimize" }

    configuration { "gmake" }
        buildoptions { "-std=c++1y" }

    configuration { "vs*" }
        buildoptions { "/wd4706" }

project("Blueprint")
    kind("ConsoleApp")
    language("C++")

    links { "BlueprintCore", "BlueprintClang" }

    includedirs { "../source" }

    files {
        "../source/BlueprintApp/**.hpp",
        "../source/BlueprintApp/**.cpp"
    }

    AddExternClangLib()
    AddExternClara()
    AddExternFileSystem()
    AddExternSqlite()

project("BlueprintCore")
    kind("StaticLib")
    language("C++")

    links { "BlueprintClang" }

    includedirs { "../source" }

    files {
        "../source/Blueprint/**.hpp",
        "../source/Blueprint/**.cpp"
    }

    if usePrecompiledHeaders then
        pchheader("Blueprint/Precompiled.hpp")
        pchsource("../source/Blueprint/Precompiled.cpp")

        configuration { "vs*" }
            buildoptions { "/FI\"Blueprint\\Precompiled.hpp\"" }
    end

    AddExternClangLib()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()

project("BlueprintCore.Test")
    kind("ConsoleApp")
    language("C++")

    links { "TestHelpers", "BlueprintCore" }

    includedirs { "../source", "../test/unit" }

    files {
        "../test/unit/Blueprint.Test/**.hpp",
        "../test/unit/Blueprint.Test/**.cpp"
    }

    if usePrecompiledHeaders then
        pchheader("Blueprint.Test/Precompiled.hpp")
        pchsource("../test/unit/Blueprint.Test/Precompiled.cpp")

        configuration { "vs*" }
            buildoptions { "/FI\"Blueprint.Test\\Precompiled.hpp\"" }
    end

    configuration { "gmake" }
        postbuildcommands { "$(TARGET) ../../test/unit/Blueprint.Test" }

    configuration { "vs*" }
        postbuildcommands { "\"$(TargetPath)\" ../../test/unit/Blueprint.Test" }

    AddExternClangLib()
    AddExternCatch()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()

project("BlueprintClang")
    kind("StaticLib")
    language("C++")

    includedirs { "../source" }

    files {
        "../source/BlueprintClang/**.hpp",
        "../source/BlueprintClang/**.cpp"
    }

    if usePrecompiledHeaders then
        pchheader("BlueprintClang/Precompiled.hpp")
        pchsource("../source/BlueprintClang/Precompiled.cpp")

        configuration { "vs*" }
            buildoptions { "/FI\"BlueprintClang\\Precompiled.hpp\"" }
    end

    AddExternClangLib()

project("TestHelpers")
    kind("StaticLib")
    language("C++")

    links { "BlueprintClang" }

    includedirs { "../source", "../test/unit" }

    files {
        "../test/unit/TestHelpers/**.hpp",
        "../test/unit/TestHelpers/**.cpp"
    }

    if usePrecompiledHeaders then
        pchheader("TestHelpers/Precompiled.hpp")
        pchsource("../test/unit/TestHelpers/Precompiled.cpp")

        configuration { "vs*" }
            buildoptions { "/FI\"TestHelpers\\Precompiled.hpp\"" }
    end

    AddExternClangLib()
    AddExternFileSystem()
