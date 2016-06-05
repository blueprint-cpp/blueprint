#pragma once

namespace blueprint
{
    class File
    {
    public:
        void SetFile(const filesystem::path& file);
        const filesystem::path& GetFile() const;

    public:
        using Dependencies = std::vector<std::shared_ptr<File>>;

        void AddDependency(std::shared_ptr<File> file);
        const Dependencies& GetDependencies() const;

    public:
        bool IsSource() const;
        bool IsHeader() const;

    private:
        Dependencies dependencies_;
        filesystem::path file_;
    };
}
