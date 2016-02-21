-- premake5.lua

require("extern.catch")
require("extern.clang")
require("extern.json")

function GenerateSolution()
    solution( "Probe" )

    configurations { "Debug", "Release" }
        location( _ACTION )

    configuration( "Debug" )
        targetdir( "../output/bin/Debug" )
        objdir( "../output/obj" )

    configuration( "Release" )
        targetdir( "../output/bin/Release" )
        objdir( "../output/obj" )

    InitExternClang()

    AddExeProject( "ProbeApp", "../source/ProbeApp", "Probe", { "Probe" } )
    AddLibProject( "Probe", "../source/Probe" )
    AddTestProject( "Probe.Test", "../test/Probe.Test", { "Probe" } )
end

function AddProject( projectName, sourcePath, projectKind, targetName, projectDependencies )
    project( projectName )
        targetname( targetName )
        kind( projectKind )
        language( "C++" )

    AddExternCatch()
    AddExternClang()
    AddExternJson()

    links(projectDependencies)

    includedirs { "../source" }

    files {
        path.join( sourcePath, "**.h" ),
        path.join( sourcePath, "**.hpp" ),
        path.join( sourcePath, "**.cpp" )
    }

    configuration { "Debug" }
        defines { "DEBUG" }
        flags { "ExtraWarnings", "FatalWarnings", "Symbols" }

    configuration { "Release" }
        defines { "NDEBUG" }
        flags { "ExtraWarnings", "FatalWarnings", "Optimize" }

    configuration { "gmake" }
        buildoptions { "-std=c++11", "-std=c++1y" }

    configuration { "vs*" }
        buildoptions { "/wd4706" }
end

function AddLibProject( projectName, sourcePath )
    AddProject( projectName, sourcePath, "StaticLib", projectName )
end

function AddExeProject( projectName, sourcePath, targetName, projectDependencies )
    if targetName then
        AddProject( projectName, sourcePath, "ConsoleApp", targetName, projectDependencies )
    else
        AddProject( projectName, sourcePath, "ConsoleApp", projectName, projectDependencies )
    end
end

function AddTestProject( projectName, sourcePath, projectDependencies )
    AddExeProject( projectName, sourcePath, projectName, projectDependencies )

    configuration { "gmake" }
        postbuildcommands { "$(TARGET) ../../test/Probe.Test/Samples" }

    configuration { "vs*" }
        postbuildcommands { "\"$(TargetPath)\" ../../test/Probe.Test/Samples" }
end

if _ACTION then
    GenerateSolution()
end
