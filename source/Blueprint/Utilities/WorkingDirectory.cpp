#include "Blueprint/Utilities/WorkingDirectory.hpp"

#if defined(_MSC_VER)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

namespace blueprint
{
    void WorkingDirectory::SetCurrent(const std::string& directory)
    {
    #if defined(_MSC_VER)
        SetCurrentDirectory(directory.c_str());
    #else
        chdir(directory.c_str());
    #endif
    }

    std::string WorkingDirectory::GetCurrent()
    {
        char cwd[256];

    #if defined(_MSC_VER)
        GetCurrentDirectory(sizeof(cwd), cwd);
    #else
        getcwd(cwd, sizeof(cwd));
    #endif

        return cwd;
    }
}
