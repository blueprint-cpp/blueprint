#pragma once

namespace blueprint
{
    class FileSystem
    {
    public:
        virtual std::unique_ptr<std::istream> OpenStream(const filesystem::path& file);
    };
}
