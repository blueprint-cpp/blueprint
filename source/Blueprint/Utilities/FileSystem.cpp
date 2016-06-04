#include "Blueprint/Utilities/FileSystem.hpp"

namespace blueprint
{
    std::unique_ptr<std::istream> FileSystem::Open(const filesystem::path& file)
    {
        auto stream = std::make_unique<std::ifstream>(file.str());
        return stream->is_open() ? std::move(stream) : nullptr;
    }
}
