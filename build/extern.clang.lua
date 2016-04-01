-- extern.clang.lua

function AddExternClangLib()
    configuration {} -- reset filter

    local libclang = nil
    local libclangPath = nil

    if os.is("macosx") then
        libclang = "clang"
        libclangPath = "/usr/local/opt/llvm38/lib/llvm-3.8/lib"
    elseif os.is("linux") then
        if os.findlib("libclang-3.8.so.1", "/usr/lib/llvm-3.8/lib") then
          libclang = ":libclang-3.8.so.1"
          libclangPath = "/usr/lib/llvm-3.8/lib"
        elseif os.findlib("clang", "/usr/lib/llvm-3.7/lib") then
          libclang = "libclang"
          libclangPath = "/usr/lib/llvm-3.7/lib"
        end
    elseif os.is("windows") then
        libclang = "libclang"
        libclangPath = "dependencies/llvm/lib"
    end

    includedirs { "../externs/clang/include" }
    libdirs     { libclangPath }

    defines {
        "__STDC_LIMIT_MACROS",
        "__STDC_CONSTANT_MACROS"
    }

    links { libclang }

    if os.get() == "windows" then
        prebuildcommands { "copy " .. path.translate("../dependencies/llvm/bin/libclang.dll") .. " $(TargetDir)" }
    else
        linkoptions { "-Xlinker -rpath " .. libclangPath }
    end
end
