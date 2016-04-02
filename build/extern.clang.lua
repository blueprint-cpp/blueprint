-- extern.clang.lua

function AddExternClangLib()
    configuration {} -- reset filter

    local libclang = nil
    local libclangPath = nil

    if os.is("macosx") then
        libclang = "clang"
        libclangPath = "/usr/local/opt/llvm38/lib/llvm-3.8"
    elseif os.is("linux") then
        if os.findlib("libclang-3.8.so.1", "/usr/lib/llvm-3.8/lib") then
          libclang = ":libclang-3.8.so.1"
          libclangPath = "/usr/lib/llvm-3.8"
        elseif os.findlib("libclang-3.7.so.1", "/usr/lib/llvm-3.7/lib") then
          libclang = ":libclang-3.7.so.1"
          libclangPath = "/usr/lib/llvm-3.7"
        end
    elseif os.is("windows") then
        libclang = "libclang"
        libclangPath = "../dependencies/store/llvm"
    end

    libclangInclude = path.join(libclangPath, "include")
    libclangLibrary = path.join(libclangPath, "lib")

    includedirs { libclangInclude }
    libdirs     { libclangLibrary }

    defines {
        "__STDC_LIMIT_MACROS",
        "__STDC_CONSTANT_MACROS"
    }

    links { libclang }

    if os.get() == "windows" then
        prebuildcommands { "copy " .. path.translate("../../dependencies/store/llvm/bin/libclang.dll") .. " $(TargetDir)" }
    else
        linkoptions { "-Xlinker -rpath " .. libclangLibrary }
    end
end
