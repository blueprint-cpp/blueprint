#pragma once

namespace blueprint { class File; }
namespace blueprint { class FileSystem; }

namespace blueprint
{
    class FileManager
    {
    public:
        FileManager(FileSystem& fileSystem);

        FileSystem& GetFileSystem();

        std::shared_ptr<File> GetOrCreateFile(const filesystem::path& filename);

        void GatherFiles(std::vector<const File*>& files) const;

    private:
        std::map<std::string, std::shared_ptr<File>> files_;

        FileSystem& fileSystem_;
    };
}
