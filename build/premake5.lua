
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

    AddExeProject( "ProbeApp", "../source/ProbeApp", "Probe" )
    AddLibProject( "Probe", "../source/Probe" )
    AddTestProject( "Probe.Test", "../test/Probe.Test" )
end

function AddProject( projectName, sourcePath, projectKind, targetName )
    project( projectName )
        targetname( targetName )
        kind( projectKind )
        language( "C++" )

    includedirs { "../externs/philsquared" }
    includedirs { "../externs/nlohmann" }
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
end

function AddLibProject( projectName, sourcePath )
    AddProject( projectName, sourcePath, "SharedLib", projectName )
end

function AddExeProject( projectName, sourcePath, targetName )
    if targetName then
        AddProject( projectName, sourcePath, "ConsoleApp", targetName )
    else
        AddProject( projectName, sourcePath, "ConsoleApp", projectName )
    end
end

function AddTestProject( projectName, sourcePath )
    AddExeProject( projectName, sourcePath )

    configuration { "gmake" }
        postbuildcommands { "$(TARGET)" }

    configuration { "vs*" }
        postbuildcommands { "\"$(TargetPath)\"" }
end

if _ACTION then
    GenerateSolution()
end
