-- extern.clang.lua

local llvm  = {}
local clang = {}

local CLANG_PATH = nil
local LLVM_CONFIG_EXE = path.join(CLANG_PATH, "bin/llvm-config")

if os.get() == "windows" then
    LLVM_CONFIG_EXE = LLVM_CONFIG_EXE .. ".exe"
end

local function GetLLVMConfigValue(config)
    local command = path.getabsolute(LLVM_CONFIG_EXE) .. " --" .. config

    return os.outputof(command)
end

local function GetLLVMConfigValues(pattern, config)
    local matchedValues = {}
    local allValues = string.explode(GetLLVMConfigValue(config), " ")

    for k, v in ipairs(allValues) do
        if v:startswith(pattern) then
            local matchedValue = v:gsub(pattern, "")
            table.insert(matchedValues, matchedValue)
        end
    end

    return matchedValues
end

function InitExternClangTooling()
    if os.isfile(LLVM_CONFIG_EXE) == false then
        print("extern.clang: llvm-config not found, cannot configure clang...")
        print()
        return
    end

    llvm.includedirs = GetLLVMConfigValues("-I", "cppflags")
    llvm.defines     = GetLLVMConfigValues("-D", "cppflags")

    llvm.libdirs = GetLLVMConfigValues("-L", "ldflags")
    llvm.syslibs = GetLLVMConfigValues("-l", "system-libs")
    llvm.libs    = GetLLVMConfigValues("-l", "libs")

    clang.libs = {
        "clangTooling",
        "clangFrontendTool",
        "clangFrontend",
        "clangDriver",
        "clangSerialization",
        "clangCodeGen",
        "clangParse",
        "clangSema",
        "clangStaticAnalyzerFrontend",
        "clangStaticAnalyzerCheckers",
        "clangStaticAnalyzerCore",
        "clangAnalysis",
        "clangARCMigrate",
        "clangRewrite",
        "clangRewriteFrontend",
        "clangEdit",
        "clangAST",
        "clangLex",
        "clangBasic"
    }
end

function AddExternClangTooling()
    configuration {} -- reset filter

    if os.isfile(LLVM_CONFIG_EXE) == false then
        return
    end

    defines { "EXTERN_CLANG_ENABLED" }

    includedirs(llvm.includedirs)
    libdirs(llvm.libdirs)

    defines(llvm.defines)

    links(clang.libs)
    links(llvm.libs)

    if os.get() == "macosx" then
        links(llvm.syslibs)
    end

    configuration { "vs*" }
        buildoptions {
            "/wd4100",
            "/wd4141",
            "/wd4244",
            "/wd4310",
            "/wd4458",
            "/wd4800"
        }
end

function AddExternClangLib()
    configuration {} -- reset filter

    local libclang = nil
    local libclangPath = nil

    if os.get() == "macosx" then
        libclang = "clang"
        libclangPath = "/usr/local/opt/llvm37/lib/llvm-3.7/lib"
    elseif os.get() == "linux" then
        libclang = ":libclang-3.7.so.1"
        libclangPath = "/usr/lib/llvm-3.7/lib"
    elseif os.get() == "windows" then
        libclang = "libclang"
        libclangPath = "../externs/llvm-3.8.0/lib"
    end

    defines { "EXTERN_CLANG_ENABLED" }

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
