#include "Blueprint/Workspace/File.hpp"

#include "Blueprint/Utilities/FileSystem.hpp"

namespace blueprint
{
    namespace internal
    {
        std::string& ltrim(std::string& s)
        {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::ptr_fun<int, int>(std::isgraph)));
            return s;
        }

        std::string& rtrim(std::string& s)
        {
            s.erase(std::find_if(s.rbegin(), s.rend(),
            std::ptr_fun<int, int>(std::isgraph)).base(), s.end());
            return s;
        }

        std::string& trim(std::string& s)
        {
            return ltrim(rtrim(s));
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

    void File::ReadDependencies(FileSystem& fileSystem, const filesystem::path& file)
    {
        auto dependencyFile = fileSystem.Open(file);

        if (dependencyFile.get())
        {
            std::string line;
            std::getline(*dependencyFile, line, ':');

            while (std::getline(*dependencyFile, line, '\\'))
            {
                auto dependency = std::make_shared<File>();
                dependency->SetFile(internal::trim(line));
                AddDependency(dependency);
            }
        }
    }
}
