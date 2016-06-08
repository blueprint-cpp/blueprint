#pragma once

#include "Blueprint/Utilities/FileSystem.hpp"

namespace blueprint
{
namespace unittest
{
    class FakeFileSystem : public FileSystem
    {
    public:
        virtual std::unique_ptr<std::istream> OpenStream(const filesystem::path& file) override;

        void AddFile(const filesystem::path& file, const std::string& buffer);

    private:
        std::map<std::string, std::string> files_;
    };
}
}
