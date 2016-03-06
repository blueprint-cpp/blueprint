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

    local libclangPath = nil

    if os.get() == "macosx" then
        libclangPath = "/usr/local/opt/llvm37/lib/llvm-3.7/lib"
    elseif os.get() == "linux" then
        libclangPath = "/usr/lib/llvm-3.7/lib"
    else
        return
    end

    defines { "EXTERN_CLANG_ENABLED" }

    includedirs { "../externs/clang/include" }
    libdirs     { libclangPath }

    defines {
        "__STDC_LIMIT_MACROS",
        "__STDC_CONSTANT_MACROS"
    }

    links { "clang-3.7" }

    linkoptions { "-Xlinker -rpath " .. libclangPath }
end
