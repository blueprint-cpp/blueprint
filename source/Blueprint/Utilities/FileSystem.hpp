#pragma once

namespace blueprint
{
    class FileSystem
    {
    public:
        virtual std::unique_ptr<std::istream> Open(const filesystem::path& file);
    };
}
