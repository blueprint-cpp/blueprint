#include "Blueprint/Workspace/File.hpp"

#include "Blueprint/Utilities/FileSystem.hpp"
#include "Blueprint/Workspace/FileManager.hpp"

namespace blueprint
{
    namespace internal
    {
        std::string& TrimLeft(std::string& s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::ptr_fun<int, int>(std::isgraph)));
            return s;
        }

        std::string& TrimRight(std::string& s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
            std::ptr_fun<int, int>(std::isgraph)).base(), s.end());
            return s;
        }

        std::string& Trim(std::string& s)
        {
            return TrimLeft(TrimRight(s));
        }
    }

    void File::SetFile(const filesystem::path& file)
    {
        file_ = file;
    }

    const filesystem::path& File::GetFile() const
    {
        return file_;
    }

    void File::SetTimestamp(std::time_t timestamp)
    {
        timestamp_ = timestamp;
    }

    std::time_t File::GetTimestamp() const
    {
        return timestamp_;
    }

    bool File::IsSource() const
    {
        auto extension = file_.extension();

        return extension == "c"
            || extension == "cc"
            || extension == "cpp";
    }

    bool File::IsHeader() const
    {
        auto extension = file_.extension();

        return extension == "h"
            || extension == "hh"
            || extension == "hpp";
    }

    void File::AddDependency(std::shared_ptr<File> file)
    {
        dependencies_.push_back(file);
    }

    const File::Dependencies& File::GetDependencies() const
    {
        return dependencies_;
    }

    void File::ReadDependencies(FileManager& fileManager, const filesystem::path& file)
    {
        auto dependencyFile = fileManager.GetOrCreateFile(file);
        auto dependencyFileStream = fileManager.GetFileSystem().OpenStream(file);

        if (dependencyFileStream)
        {
            std::string line;
            std::getline(*dependencyFileStream, line, ':');

            while (std::getline(*dependencyFileStream, line, '\\'))
            {
                AddDependency(fileManager.GetOrCreateFile(internal::Trim(line)));
            }
        }
    }
}
