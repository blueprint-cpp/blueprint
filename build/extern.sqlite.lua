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
        --sqliteInclude = "todo"
        --sqliteLibrary = "todo"
        return
    end

    includedirs { sqliteInclude}
    libdirs     { sqliteLibrary }

    links { "sqlite3" }
end
