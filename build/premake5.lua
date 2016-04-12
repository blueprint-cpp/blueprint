-- premake5.lua

require("extern.clang")
require("extern.filesystem")
require("extern.json")
require("extern.philsquared")
require("extern.sqlite")

local usePrecompiledHeaders = true

local function AddPrecompiledHeader(header, source)
    if not usePrecompiledHeaders then
        return
    end

    pchheader(header)
    pchsource(source)

    configuration { "vs*" }
        buildoptions { "/FI\"" .. path.translate(header) .."\"" }
end

local function AddPostBuildUnitTest(args)
    configuration { "gmake" }
        postbuildcommands { "$(TARGET) " .. (args or "") }

    configuration { "vs*" }
        postbuildcommands { "\"$(TargetPath)\" " .. (args or "") }
end

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

    links { "BlueprintCore", "BlueprintClang", "BlueprintReflection" }

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

    links { "BlueprintClang", "BlueprintReflection" }

    includedirs { "../source" }

    files {
        "../source/Blueprint/**.hpp",
        "../source/Blueprint/**.cpp"
    }

    AddPrecompiledHeader("Blueprint/Precompiled.hpp", "../source/Blueprint/Precompiled.cpp")

    AddExternClangLib()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()

project("BlueprintCore.Test")
    kind("ConsoleApp")
    language("C++")

    links { "TestHelpers", "BlueprintCore", "BlueprintClang", "BlueprintReflection" }

    includedirs { "../source", "../test/unit" }

    files {
        "../test/unit/Blueprint.Test/**.hpp",
        "../test/unit/Blueprint.Test/**.cpp"
    }

    AddPrecompiledHeader("Blueprint.Test/Precompiled.hpp", "../test/unit/Blueprint.Test/Precompiled.cpp")
    AddPostBuildUnitTest("../../test/unit/Blueprint.Test")

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

    AddPrecompiledHeader("BlueprintClang/Precompiled.hpp", "../source/BlueprintClang/Precompiled.cpp")

    AddExternClangLib()

project("BlueprintReflection")
    kind("StaticLib")
    language("C++")

    includedirs { "../source" }

    files {
        "../source/BlueprintReflection/**.hpp",
        "../source/BlueprintReflection/**.cpp"
    }

    AddPrecompiledHeader("BlueprintReflection/Precompiled.hpp", "../source/BlueprintReflection/Precompiled.cpp")

    AddExternFileSystem()

project("BlueprintReflection.Test")
    kind("ConsoleApp")
    language("C++")

    links { "TestHelpers", "BlueprintReflection" }

    includedirs { "../source", "../test/unit" }

    files {
        "../test/unit/BlueprintReflection.Test/**.hpp",
        "../test/unit/BlueprintReflection.Test/**.cpp"
    }

    AddPrecompiledHeader("BlueprintReflection.Test/Precompiled.hpp", "../test/unit/BlueprintReflection.Test/Precompiled.cpp")
    AddPostBuildUnitTest()

    AddExternCatch()
    AddExternFileSystem()

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
