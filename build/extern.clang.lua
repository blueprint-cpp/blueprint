-- extern.clang.lua

function AddExternClangLib()
    configuration {} -- reset filter

    local libclang = nil
    local libclangPath = nil

    if os.get() == "macosx" then
        libclang = "clang"
        libclangPath = "/usr/local/opt/llvm38/lib/llvm-3.8/lib"
    elseif os.get() == "linux" then
        libclang = ":libclang-3.8.so.1"
        libclangPath = "/usr/lib/llvm-3.8/lib"
    elseif os.get() == "windows" then
        libclang = "libclang"
        libclangPath = "../externs/llvm-3.8.0/lib"
    end

    includedirs { "../externs/clang/include" }
    libdirs     { libclangPath }

    defines {
        "__STDC_LIMIT_MACROS",
        "__STDC_CONSTANT_MACROS"
    }

    links { libclang }

    if os.get() == "windows" then
        prebuildcommands { "copy " .. path.translate("../../externs/llvm-3.8.0/bin/libclang.dll") .. " $(TargetDir)" }
    else
        linkoptions { "-Xlinker -rpath " .. libclangPath }
    end
end
