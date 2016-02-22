-- extern.clang.lua

local llvm  = {}
local clang = {}

local CLANG_PATH = nil
local LLVM_CONFIG_EXE = path.join(CLANG_PATH, "bin/llvm-config")

local function GetLLVMConfigValue(config)
    return os.outputof(LLVM_CONFIG_EXE .. " --" .. config)
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

function InitExternClang()
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

function AddExternClang()
    if os.isfile(LLVM_CONFIG_EXE) == false then
        return
    end

    includedirs(llvm.includedirs)
    libdirs(llvm.libdirs)

    defines(llvm.defines)

    links(clang.libs)
    links(llvm.libs)

    if os.get() == "macosx" then
        links(llvm.syslibs)
    end
end
