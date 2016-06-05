#include "Blueprint/Workspace/File.hpp"

namespace blueprint
{
    void File::SetFile(const filesystem::path& file)
    {
        file_ = file;
    }

    const filesystem::path& File::GetFile() const
    {
        return file_;
    }

    void File::AddDependency(std::shared_ptr<File> file)
    {
        dependencies_.push_back(file);
    }

    const File::Dependencies& File::GetDependencies() const
    {
        return dependencies_;
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
}
