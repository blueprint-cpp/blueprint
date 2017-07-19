-- premake5.lua

require("extern.clang")
require("extern.filesystem")
require("extern.json")
require("extern.philsquared")
require("extern.sqlite")

local usePrecompiledHeaders = true

local function GetUnitTestArguments()
    if os.getenv("APPVEYOR") then
        return " --reporter junit --out $(OutDir)$(TargetName).results.xml"
    else
        return ""
    end
end

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

local function GenerateWorkspace()
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

    configuration {} -- reset filter

    --buildoptions { "-v" }
    --linkoptions { "-v" }
end

local function GenerateBlueprint()
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
end

local function GenerateBlueprintCore()
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
end

local function GenerateBlueprintCoreTest()
    project("BlueprintCore.Test")
    kind("ConsoleApp")
    language("C++")

    links { "TestHelpers", "BlueprintCore", "BlueprintClang", "BlueprintReflection" }

    includedirs { "../test/unit", "../source" }

    files {
        "../test/unit/Blueprint.Test/**.hpp",
        "../test/unit/Blueprint.Test/**.cpp"
    }

    AddPrecompiledHeader("Blueprint.Test/Precompiled.hpp", "../test/unit/Blueprint.Test/Precompiled.cpp")
    AddPostBuildUnitTest(GetUnitTestArguments())

    AddExternClangLib()
    AddExternCatch()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()
end

local function GenerateBlueprintClang()
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
end

local function GenerateBlueprintReflection()
    project("BlueprintReflection")
    kind("StaticLib")
    language("C++")

    includedirs { "../source" }

    files {
        "../source/BlueprintReflection/**.hpp",
        "../source/BlueprintReflection/**.cpp"
    }

    AddPrecompiledHeader("BlueprintReflection/Precompiled.hpp", "../source/BlueprintReflection/Precompiled.cpp")
end

local function GenerateBlueprintReflectionTest()
    project("BlueprintReflection.Test")
    kind("ConsoleApp")
    language("C++")

    links { "BlueprintReflection" }

    includedirs { "../test/unit", "../source" }

    files {
        "../test/unit/BlueprintReflection.Test/**.hpp",
        "../test/unit/BlueprintReflection.Test/**.cpp"
    }

    AddPrecompiledHeader("BlueprintReflection.Test/Precompiled.hpp", "../test/unit/BlueprintReflection.Test/Precompiled.cpp")
    AddPostBuildUnitTest(GetUnitTestArguments())

    AddExternCatch()
end

local function GenerateTestHelpers()
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
end

GenerateWorkspace()
GenerateBlueprint()
GenerateBlueprintCore()
GenerateBlueprintCoreTest()
GenerateBlueprintClang()
GenerateBlueprintReflection()
GenerateBlueprintReflectionTest()
GenerateTestHelpers()
