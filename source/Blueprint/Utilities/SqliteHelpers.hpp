#pragma once

#include <sqlite3pp/sqlite3pp.h>

namespace blueprint
{
namespace sqlite
{
    namespace internal
    {
        template<typename Value>
        void Bind(sqlite3pp::statement& statement, int index, Value value)
        {
            statement.bind(index, (int)value);
        }

        void Bind(sqlite3pp::statement& statement, int index, float value)
        {
            statement.bind(index, value);
        }

        void Bind(sqlite3pp::statement& statement, int index, double value)
        {
            statement.bind(index, value);
        }

        void Bind(sqlite3pp::statement& statement, int index, const char* value)
        {
            statement.bind(index, value, sqlite3pp::nocopy);
        }

        void Bind(sqlite3pp::statement& statement, int index, const std::string& value)
        {
            statement.bind(index, value.c_str(), sqlite3pp::copy);
        }

        template<typename Value, typename... Args>
        void RecursiveBind(sqlite3pp::statement& /*statement*/, int /*index*/)
        {}

        template<typename Value, typename... Args>
        void RecursiveBind(sqlite3pp::statement& statement, int index, Value&& value)
        {
            Bind(statement, index, std::forward<Value>(value));
        }

        template<typename Value, typename... Args>
        void RecursiveBind(sqlite3pp::statement& statement, int index, Value&& value, Args&&... args)
        {
            Bind(statement, index, std::forward<Value>(value));
            RecursiveBind(statement, index + 1, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    int ExecuteCommand(sqlite3pp::command& cmd, Args&&... args)
    {
        cmd.reset();
        internal::RecursiveBind(cmd, 1, args...);
        return cmd.execute();
    }
}
}
