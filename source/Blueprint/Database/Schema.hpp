#pragma once

#include <sqlite3pp/sqlite3pp.h>

namespace blueprint
{
namespace database
{
    class Schema
    {
    public:
        Schema(sqlite3pp::database& db);

        Schema(const Schema& other) = delete;
        Schema& operator=(const Schema& other) = delete;

        void Initialize();

    private:
        void CreateTables();
        void CreateSourceFile();
        void CreateSourceLocation();
        void CreateNamespace();
        void CreateType();

    private:
        sqlite3pp::database& db_;
    };
}
}
