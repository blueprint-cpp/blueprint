#include "Blueprint/Workspace/FileManager.hpp"

#include "Blueprint/Utilities/FileSystem.hpp"
#include "Blueprint/Workspace/File.hpp"

namespace blueprint
{
    FileManager::FileManager(FileSystem& fileSystem)
        : fileSystem_(fileSystem)
    {}

    FileSystem& FileManager::GetFileSystem()
    {
        return fileSystem_;
    }

    std::shared_ptr<File> FileManager::GetOrCreateFile(const filesystem::path& filename)
    {
        auto fileIt = files_.find(filename.str());

        if (fileIt != files_.end())
        {
            return fileIt->second;
        }

        auto file = std::make_shared<File>();
        file->SetFile(filename);

        files_[filename.str()] = file;

        return file;
    }

    void FileManager::GatherFiles(std::vector<const File*>& files) const
    {
        for (auto& kv : files_)
        {
            files.push_back(kv.second.get());
        }
    }
}
