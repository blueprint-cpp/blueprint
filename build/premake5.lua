-- premake5.lua

require("extern.clang")
require("extern.filesystem")
require("extern.json")
require("extern.philsquared")
require("extern.sqlite")

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

project("BlueprintApp")
    targetname("Blueprint")
    kind("ConsoleApp")
    language("C++")

    links { "Blueprint" }

    includedirs {
        "../source",
    }

    files {
        "../source/BlueprintApp/**.hpp",
        "../source/BlueprintApp/**.cpp"
    }

    AddExternClangLib()
    AddExternClara()
    AddExternFileSystem()
    AddExternSqlite()

project("Blueprint")
    kind("StaticLib")
    language("C++")

    includedirs { "../source" }

    files {
        "../source/Blueprint/**.hpp",
        "../source/Blueprint/**.cpp"
    }

    AddExternClangLib()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()

project("Blueprint.Test")
    kind("ConsoleApp")
    language("C++")

    links { "Blueprint" }

    includedirs {
        "../source",
        "../test/unit"
    }

    files {
        "../test/unit/**.hpp",
        "../test/unit/**.cpp"
    }

    configuration { "gmake" }
        postbuildcommands { "$(TARGET) ../../test/unit/Blueprint.Test" }

    configuration { "vs*" }
        postbuildcommands { "\"$(TargetPath)\" ../../test/unit/Blueprint.Test" }

    AddExternClangLib()
    AddExternCatch()
    AddExternFileSystem()
    AddExternJson()
    AddExternSqlite()
