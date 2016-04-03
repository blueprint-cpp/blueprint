-- extern.sqlite.lua

function AddExternSqlite()
    configuration {} -- reset filter

    local sqliteInclude = nil
    local sqliteLibrary = nil

    if os.get() == "macosx" then
        sqliteInclude = "/usr/local/opt/sqlite/include"
        sqliteLibrary = "/usr/local/opt/sqlite/lib"
    elseif os.get() == "linux" then
        sqliteInclude = "/usr/include"
        sqliteLibrary = "/usr/lib/x86_64-linux-gnu"
    elseif os.get() == "windows" then
        sqliteInclude = "../dependencies/store/sqlite/include"
        sqliteLibrary = "../dependencies/store/sqlite/lib"
    end

    includedirs { sqliteInclude, "../source/Externs/sqlite" }

    if sqliteLibrary then
        libdirs { sqliteLibrary }
        links { "sqlite3" }
    end

    if os.get() == "windows" then
        prebuildcommands { "copy " .. path.translate("../../dependencies/store/sqlite/lib/sqlite3.dll") .. " $(TargetDir)" }
    end
end
