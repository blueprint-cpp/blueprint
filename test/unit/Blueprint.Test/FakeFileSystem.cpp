#include "Blueprint.Test/FakeFileSystem.hpp"

#include "TestHelpers/MemoryInputStream.hpp"

namespace blueprint
{
namespace unittest
{
    std::unique_ptr<std::istream> FakeFileSystem::Open(const filesystem::path& file)
    {
        auto entry = files_.find(file.str());

        if (entry != files_.end())
        {
            auto& buffer = entry->second;
            return std::make_unique<MemoryInputStream>((const uint8_t*)buffer.data(), buffer.length());
        }

        return nullptr;
    }

    void FakeFileSystem::AddFile(const filesystem::path& file, const std::string& buffer)
    {
        files_[file.str()] = buffer;
    }
}
}
