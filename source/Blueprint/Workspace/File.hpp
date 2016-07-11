#pragma once

namespace blueprint { class FileManager; }

namespace blueprint
{
    class File
    {
    public:
        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

        void SetTimestamp(std::time_t timestamp);
        std::time_t GetTimestamp() const;

        bool IsSource() const;
        bool IsHeader() const;

    public:
        using Dependencies = std::vector<std::shared_ptr<File>>;

        void AddDependency(std::shared_ptr<File> file);
        const Dependencies& GetDependencies() const;

        void ReadDependencies(FileManager& fileManager, const filesystem::path& file);

    private:
        Dependencies dependencies_;
        filesystem::path file_;

        std::time_t timestamp_{0};
    };
}
