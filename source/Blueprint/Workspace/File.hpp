#pragma once

namespace blueprint { class FileSystem; }

namespace blueprint
{
    class File
    {
    public:
        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

        bool IsSource() const;
        bool IsHeader() const;

    public:
        using Dependencies = std::vector<std::shared_ptr<File>>;

        void AddDependency(std::shared_ptr<File> file);
        const Dependencies& GetDependencies() const;

        void ReadDependencies(FileSystem& fileSystem, const filesystem::path& file);

    private:
        Dependencies dependencies_;
        filesystem::path file_;
    };
}
